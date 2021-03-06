#Scrape
import urllib3
from bs4 import BeautifulSoup
import csv

#class holds all properties of webpages
class WebPage:
    def __init__(self, url, index, links):
        self.url = url #string url
        self.title = url[6:] #string webpage title from url
        self.index = index #int index (unique id)
        self.links = links #list of webpages
        self.outbounds = []

#only index some link types
def is_valid(url):
    """given an internal /wiki/ link, determine if it is valid for scraping"""
    for s in invalid_snippets:
        if s in url:
            return False
    return True

#get all valid links from a marvel wikia page
def make_page(init_url, index):
    """A function that, given a url from a marvel.wikia.com page (string)
    returns all internal /wiki/ links from that page's main article"""
    http = urllib3.PoolManager()
    req = http.request('GET', 'http://marvel.wikia.com' + init_url)
    if req.status != 200:
        print("Error: ", req.status, " skipping page")
        return None #don't index dead links
    page = req.data
    soup = BeautifulSoup(page, 'lxml')
    #Limit to URLS within the main article
    for art in soup.find_all('article'):
        if art['id'] == 'WikiaMainContent':
            article = art
    #make page
    page = WebPage(init_url, index, [])
    title = soup.find('h1', {'class':'page-header__title'})
    page.title = title.text
    for link in article.find_all('a'):
        url = link.get('href')
        #Sometimes bs4 messes up and gives none instead of a string
        if url is None:
            continue #to next link
        #Filter links to only internal wiki links
        if '/wiki/' in url and 'http' not in url:
            url = url.split('?')[0] # drop arguments
            if is_valid(url):
                page.links.append(url)
    checked_urls.append(init_url)
    return page

if __name__ == "__main__":
    #scrape this link http://marvel.wikia.com/wiki/Anthony_Stark_(Earth-616)
    #only data from article id WikiaMainContent
    dex = 0
    checked_urls = [] #global, modified in make_page
    pages = []
    invalid_snippets = ['/wiki/Category:', '/wiki/File:', '/wiki/Glossary:',
                        '/wiki/Special:', '_Vol_', '_Season_', '#']
    pages.append(make_page('/wiki/Anthony_Stark_(Earth-616)', dex))
    #checked_urls append in make_page function

    #don't let this fool you: it is a while loop because it appends to the list as it moves through it
    #this will index every major page reachable from iron man (most of the major pages on the site)
    for page in pages:
        if page != None:
            for link in page.links:
                if link != None:
                    if link not in checked_urls:
                        dex += 1
                        if dex >= 600:
                            break
                        pages.append(make_page(link, dex))
                        print("indexing ", dex, " ", link)
                    else:
                        print("already indexed ", link)

    #Construct a list of scraped links to enable indexing later
    links=[]
    for page in pages:
        links.append(page.url)

    #Create outbound indices for each webpage for matrix storage
    for page in pages:
        for link in page.links:
            if link in links:
                page.outbounds.append(links.index(link))
            else:
                page.outbounds.append('nil')

    #save pages
    with open("results.csv", 'w') as output:
        w = csv.writer(output, quoting=csv.QUOTE_ALL)
        w.writerows([p.title, p.url, p.index, p.outbounds, p.links] for p in pages)
