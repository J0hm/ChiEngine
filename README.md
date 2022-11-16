# ChiEngine
A chess engine written in C++?

### Dataset: Cassiabase

	- Figure out how to extract and use games from this dataset
	- How will games be represented?
	- How will the board be represented?
	- How will moves be represented?
  
### Libraries:

	- i probably need to make these oops
	- rewrite python-chess in c++

### GUI:

	- Communication with common chess GUIs

### Important links:
- [Cassiabase Dataset](http://caissabase.co.uk/)
- [Chess Programming Wiki](https://www.chessprogramming.org/)
- [SCID](https://scid.sourceforge.net/)
- [Getting Started with Building Chess Engines](http://www.fam-petzke.de/cp_getstarted_en.shtml)
- [UCI Protocol](http://wbec-ridderkerk.nl/html/UCIProtocol.html)
  
### TODO:

  - [ ] Board representation (data structures, methods, etc)
    - Hybrid solution
  - [ ] Interface and communication with a GUI using UCI
  	- SCID over UCI
  - [ ] Evaluation algorithm
  	- Neural network trained on "pairs" of positions
  	- Create database of:
  		- Winning positions for black
  		- Winning positions for white
  	- Use pairs of these positions to train the algorithm, where winning positions are prefered over losing
  - [ ] Search algorithm
  - [ ] Create database of winning positions for black and white
