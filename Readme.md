***Adapt***

Small library for (almost) adaptive smoothing for use with arduinos.
```
To use:
   declare as:
       Adapt adapt(resolution);
   insert values using:
       adapt.insert(value);	
   get averages as:
       adapt.average();
       adapt.weighted();
       adapt.nonlinear();
       adapt.exponential();
   additionally, you can check these elements:
       newest();
       oldest();
```
todo: selection based smoothing