from bs4 import BeautifulSoup as soup
from requests import get
from requests.exceptions import RequestException
from contextlib import closing

def simple_get(url):
    try:
        with closing(get(url, stream=True)) as resp:
            if is_good_response(resp):
                return resp.content
            else:
                return None

    except RequestException as e:
        print('Error during requests to {0} : {1}'.format(url, str(e)))
        return None

def is_good_response(resp):
    content_type = resp.headers['Content-Type'].lower()
    return (resp.status_code == 200 
            and content_type is not None 
            and content_type.find('html') > -1)

print("Hello Mike!\n")

raw_html = simple_get('http://marvel.wikia.com/wiki/Marvel_Database')
html = soup(raw_html, 'html.parser')
for p in html.find_all('a', href=True, title=True):
    if p['href'].startswith('/wiki/'):
        print(p['title'])

