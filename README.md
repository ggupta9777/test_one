# What is this package? 

The package contains 4 nodes: 2 publishers and 2 subscribers, one in cpp and python each. The objective was to estimate the pub-sub rates using the following combinations:

1. python publisher - python subscriber
2. python publisher - c++ subscriber
3. c++ publisher - python subscriber
4. c++ publisher - c++ subsriber

# How to run the setup? 

The launch/ directory contains 4 launch files, one for the above cases each. Running the launch files prompts an rqt dynamic reconfigure, with the ability to alter the publish rate (depending on which publisher is running). Simulatenously, subscription rate for trailing 2 seconds is displayed. 

## Expected results: 

1. python publisher to python subscriber (pypub_pysub.launch): The rate stagnates at around 10KHz.

2. python publisher to c++ subscriber (pypub_cppsub.launch): Quite similar to the first case, the rate rarely crosses 10 KHz. Upon investing with 'rostopic hz /super_awesome_topic', the bottleneck is the rate of publishing. 

3. c++ publisher to python subscriber (cpppub_pysub.launch): The max publish rate falls around 25 KHz, even for much higher demanded loop rates.

4. c++ publisher to cpp subscriber (cpppub_cppsub.launch): The max rate stays between 25-30 KHz, comparable to the previous findings but slightly higher upon empirical observation.