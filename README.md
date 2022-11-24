# ChiEngine
A UCI chess engine written in C++ using deep neural networks for evaluation.

### Dataset: Cassiabase
	- Figure out how to extract and use games from this dataset
	- How will games be represented?
	- How will the board be represented?
	- How will moves be represented?

### GUI:
	- Communication with common chess GUIs

### Important links:
- [Cassiabase Dataset](http://caissabase.co.uk/)
- [Chess Programming Wiki](https://www.chessprogramming.org/)
- [SCID](https://scid.sourceforge.net/)
- [Getting Started with Building Chess Engines](http://www.fam-petzke.de/cp_getstarted_en.shtml)
- [UCI Protocol](http://wbec-ridderkerk.nl/html/UCIProtocol.html)
  
### TODO:
  - [ ] Finish testing parseMove. Only certain captures/edge cases left.
  - [ ] Implement and test make and unmake move.
  - [ ] Implement movegen and test using perft
  - [ ] Find a solution for storing positions to be evauluated by the neural network
  - [ ] Create a database of winning and losing positions for black/white (from Cassiabase set)
  - [ ] Train an evaluation neural network using these positions
