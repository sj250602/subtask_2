import matplotlib.pyplot as plt
import csv

queue =[]
dynamic = []
time = []

path_of_file = input("Enter path of file")

with open(path_of_file , 'r') as file:
	reader = csv.reader(file)
	for row in reader:
		time.append(float(row[0]))
		queue.append(float(row[1]))
		dynamic.append(float(row[2]))

plt.plot( time , queue , label = "queue density")

plt.plot( time , dynamic , label = "moving density")

plt.xlabel('time(in seconds)')

plt.ylabel('density')

plt.title('Traffic Density Curve')

plt.legend()

plt.show()
