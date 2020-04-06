#pragma once
#include<iostream>
#include<map>
#include<vector>
using std::vector;
using namespace std;

typedef std::pair<int,char> tpair;

/**
 * Abstract class for Deterministic Finite Automata.
 */
bool operator== (const pair<int*,char>& lhs, const pair<int*,char>& rhs);
class AbstractDFA {
	// TODO: use data structure for representing
	// - states
	// - final states (and sink states)
	// - transitions of the form (state, input) -> state
	// - current state
	public:
    vector<int> *states; 
	map<pair<int*, char>, int*> *tr;
	int* current;
	int* start;
	int* final;
    int* sink;
	void initializeVector(int n);
public:
	/**
	 * Constructor for Abstract DFA.
	 * 
	 * @param noStates
	 *            Number of states in the DFA.
	 */
	AbstractDFA(int noStates);
	~AbstractDFA();
	void defineSinkState(int i);
	void defineInitialeState(int i);
	void defineFinalState(int i);
	void defineTransaction(int* source, char c, int* destination);
	/**
	 * Reset the automaton to the initial state.
	 */
	void reset();

	/**
	 * Performs one step of the DFA for a given letter. If there is a transition
	 * for the given letter, then the automaton proceeds to the successor state.
	 * Otherwise it goes to the sink state. By construction it will stay in the
	 * sink for every input letter.
	 * 
	 * @param letter
	 *            The current input.
	 */
	virtual void doStep(char letter);
	
	/**
	 * Check if the automaton is currently accepting.
	 * 
	 * @return True, if the automaton is currently in the accepting state.
	 */
	bool isAccepting();

	/**
	 * Run the DFA on the input.
	 * 
	 * @param inputWord
	 *            stream that contains the input word
	 * @return True, if if the word is accepted by this automaton
	 */
	bool run(const string &inputWord);
};

/**
 * DFA recognizing a given word.
 */
class WordDFA : public AbstractDFA {

public:
	/**
	 * Construct a new DFA that recognizes exactly the given word. Given a word
	 * "foo" the constructed automaton looks like: -> () -f-> () -o-> () -o-> []
	 * from every state (including the final one) every other input letter leads
	 * to a distinguished sink state in which the automaton then remains
	 * 
	 * @param word
	 *            A String that the automaton should recognize
	 */
	 WordDFA(const string &word);
};

/**
 * DFA recognizing comments.
 */
class CommentDFA : public AbstractDFA {

public:
	/**
	 * Construct a new DFA that recognizes comments within source code. There
	 * are two kinds of comments: A single line comment starts with // and ends
	 * with a newline and a multiline comment that starts with / * and ends with
	 * * / (without the spaces)
	 */
	bool ok;
	int ascii;
	CommentDFA();
	
	/**
	 * Performs one step of the DFA for a given letter. This method works
	 * differently than in the superclass AbstractDFA.
	 * 
	 * @param letter
	 *            The current input.
	 */
    virtual void doStep(char letter);
	void stampa();
};

