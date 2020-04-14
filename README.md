# Page-Replacement
Page replacement alogorithms in an operating system.
Used Perl Script to represent it graphically.

All algorithms have a tendency of showing an decrease in the Page Fault When the No. of Frames increases,

But FIFO algorithm sometimes deviates from this property which was found by Belady and this phenomenon is known as Belady's Anomaly.

For an input 1,2,3,4,5,6,1,2,3,4,5,6

Here all the algorithm shows the 1st behaviour mentioned above

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/AAbar2.jpeg)

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/AAbarFrms.jpeg)

For an input 1,2,3,4,1,2,5,1,2,3,4,5

Here FIFO and RAND alone shows Belady's Anomaly

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/bar2.jpeg)

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/barFrms.jpeg)

The Average of Both the results are give by

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/avgbar2.jpeg)

![alt text](https://raw.githubusercontent.com/jaggu24/Page-Replacement/master/comparision/avgfrms.jpeg)
