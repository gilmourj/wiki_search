## Wiki Search
Operating Systems and Parallel Algorithms final project

**Authors:** Jonathan Gilmour, Philip Kiely, Mike Zou

**Description:**   
Wiki Search is a small-scale database search engine. Wiki Search takes in a database in CSV format and constructs an adjacency matrix, then calculates pagerank values based on Larry Page and Sergey Brin's PageRank algorithm. 

To use Wiki Search, clone the repository and then call "make" in terminal after navigating to the folder. After doing so, run the program by calling *./driver avengersclean.csv \[optional number of desired search results here\]*. The program will launch a UI, in which you can query search terms and will be returned results in the UI window, alog with the number of your query. If you type "quit," the program will exit.

**Sample Walkthrough:**

From the wiki_search folder:    
\> make  
\> ./driver avengersclean.csv 12  
*The UI will launch and you will be greeted*  
\> "earth"  
*12 results related to earth will be returned*  
\> "evil"  
*Only 2 results will be returned since evil is not a popular name*   
\> "Charlie Curtsinger"  
charlie curtsinger is not known to The Avengers *will be displayed*  
\> "quit"  
*exit the program*  

References:

https://www.crummy.com/software/BeautifulSoup/bs4/doc/#quick-start
