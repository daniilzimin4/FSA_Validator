# FSA Validator
This is a program that validates a Finite State Automaton (FSA) description provided in a specific format. The program reads the input from a file called fsa.txt and outputs the results to a file called result.txt.

The input file format should contain the following information:

A list of states, represented as [s1, s2, ...], where s1, s2, ... are strings containing Latin letters, words, and numbers.
An alphabet, represented as [a1, a2, ...], where a1, a2, ... are strings containing Latin letters, words, numbers, and the character _ (underscore).
An initial state, represented as [s], where s is a state from the list of states.
A list of final states, represented as [s1, s2, ...], where s1, s2, ... are states from the list of states.
Transitions, represented as [s1>a>s2, ...], where s1, s2, ... are states from the list of states, and a is a character from the alphabet.
The output file format will indicate whether the FSA is complete or incomplete, and will list any warnings that were generated during the validation process. The warnings will be sorted according to their code.

If the FSA is incomplete, the output file will contain the message "FSA is incomplete". Otherwise, the output file will indicate that the FSA is complete.

If any warnings were generated during the validation process, the output file will contain a list of warnings, sorted by code. Each warning will be identified by a code, such as "W1", and will be followed by a description of the warning.
