The script receives (either from the command line or from a *.txt file): 
- State probability distribution (i.e. the probability that the system is in each of the N states)
- Transition matrix (i.e. the matrix that gives the probability to transition from one state to another)
- Emission matrix (i.e. the matrix that gives the probability for the different emissions / events / observations given a certain state)

More specifically, given the current state probability distribution what is the probabity for the different emissions after the next transition (i.e. after the system has made a single transition)?
