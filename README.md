# Page-Replacement Sem 4

## Page replacement alogorithms in an operating system.

### Used Perl Script to represent it graphically.

**All algorithms have a tendency of showing an decrease in the Page Fault When the No. of Frames increases**

**But FIFO algorithm sometimes deviates from this property which was found by Belady and this phenomenon is known as Belady's Anomaly**

For an input 1,2,3,4,5,6,1,2,3,4,5,6

Here all the algorithm shows the 1st behaviour mentioned above

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/AAbar2.jpeg)

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/AAbarFrms.jpeg)

For an input 1,2,3,4,1,2,5,1,2,3,4,5

**Here FIFO and RAND alone shows Belady's Anomaly**

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/bar2.jpeg)

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/barFrms.jpeg)

The Average of Both the results are give by

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/avg2.jpeg)

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/avgfrms.jpeg)

*You can see than eventuall when number of frames are increased all algorithm tend to become optimum*

## How to Run
1. Type your inputs in r1.txt file
2. Specify the appropriate start, end and increment size of frame in plotAlgos.pl
3. use `perl plotAglos.pl` to plot the graphs of the input (You need to have gnuplot and imagemagic tools and their rights to execute this)
4. Your output will be visible in output.txt and the graphs will be available in your current working directory
5. Then use `perl plotFrames.pl` to see the other graph
6. Change the name of the images.
7. If you wish to calculate average hit percentage then
  - Enter the other input (with same number of elements) in r1.txt.
  - Change file name to output22.txt in plotAlgos.pl and plotFrames.pl.
  - Use `perl plotAlgos.pl` and `perl plotFrames'
  - Use `perl avgAlgos.pl` and `perl avgFrames` to see the result of the average analysis.
