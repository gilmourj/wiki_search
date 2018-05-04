#add numeric links to avengers.csv
import pandas as pd
import ast
import csv

if __name__ == "__main__":
    avengers = pd.read_csv("avengers.csv", sep='|', header=None)
    links = ast.literal_eval(avengers.iloc[0][3])
    i = 0
    all_nums = []
    for n in range(0, avengers.shape[0]):
        row = avengers.iloc[n]
        nums = []
        for link in ast.literal_eval(row[3]):
            nums.append(links.index(link))

        all_nums.append(nums)
    
    #write to csv but pipe deliminated
    with open("avengersclean.csv", 'w') as output:
        w = csv.writer(output, quoting=csv.QUOTE_ALL, delimiter='|')
        for i in range (0, len(all_nums)):
            r = avengers.iloc[i]
            w.writerow([r[0], r[1], r[2], r[3], all_nums[i]])