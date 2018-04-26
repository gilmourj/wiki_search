#Scrape
import urllib3
from bs4 import BeautifulSoup


class WebPage():
    #string url
    #title
    #index
    #list of links
    pass


def is_valid(url):
    """given an internal /wiki/ link, determine if it is valid for scraping"""
    #if the wiki page is a category not an article
    if '/wiki/Category:' in url:
        return False
    #if the wiki page is a file not an article
    if '/wiki/File:' in url:
        return False
    #if the wiki page is a glossary not an article
    if '/wiki/Glossary:' in url:
        return False
    #if internal (same page) link
    if '#' in url:
        return False
    return True


def get_links(init_url):
    """A function that, given a url from a marvel.wikia.com page (string)
    returns all internal /wiki/ links from that page's main article"""
    http = urllib3.PoolManager()
    req = http.request('GET', init_url)
    if req.status != 200:
        print('Error: status ', req.status)
        exit(2)
    page = req.data
    soup = BeautifulSoup(page, 'lxml')
    #Limit to URLS within the main article
    for art in soup.find_all('article'):
        if art['id'] == 'WikiaMainContent':
            article = art
    #List urls
    urls = []
    for link in article.find_all('a'):
        url = link.get('href')
        #Sometimes bs4 messes up and gives none
        if url is None:
            continue #to next link
        #Filter links to only internal wiki links
        if '/wiki/' in url and 'http' not in url:
            #drop ?...
            if is_valid(url):
                urls.append(url)
    return urls

if __name__ == "__main__":
    #scrape this link http://marvel.wikia.com/wiki/Anthony_Stark_(Earth-616)
    #only data from article id WikiaMainContent
    urls = get_links('http://marvel.wikia.com/wiki/Anthony_Stark_(Earth-616)')
    print(urls)
    