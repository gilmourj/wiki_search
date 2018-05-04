#add numeric links to avengers.csv
import pandas as pd


if __name__ == "__main__":
    #avengers = pd.read_csv("avengers.csv")
    links = list(avengers.iloc[1])
    
    #write to csv but pipe deliminated
    