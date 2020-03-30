//#pragma once

#include<iostream>
#include<map>
#include<vector>


using namespace std;
typedef std::pair<int,char> tpair;

// ridefinizione == per oggetti di tipo pair
 bool operator== (const pair<int*,char>& lhs, const pair<int*,char>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

/**
 * Abstract class for Deterministic Finite Automata.
 */
class AbstractDFA {
	// TODO: use data structure for representing
	// - states
	// - final states (and sink states)
	// - transitions of the form (state, input) -> state
	// - current state
	// l'identificativo degli stati comincia con il valore 0 come in jFlap.
	protected:
	vector<int> *states; 
	map<pair<int*, char>, int*> *tr;
	int* current;
	int* start;
	int* final;
    int* sink;
	void initializeVector(int n) {
		int a = 0;
		for(vector<int>::iterator it = states->begin(); it!=states->end(); it++) {
			*it = a;
			a++;
		}
	}
public:
void defineSinkState(int i) {
	sink = &((*states)[i]);
}
void defineInitialeState(int i) {
	start = &((*states)[i]);
}
void defineFinalState(int i) {
	final = &((*states)[i]);
}
/**
 * funzione per definire transizioni
*/
	void defineTransaction(int* source, char c, int* destination) {
		tr->insert(make_pair(make_pair(source, c),destination));
	}
	/**
	 * Constructor for Abstract DFA.
	 * 
	 * @param noStates
	 *            Number of states in the DFA.
	 */

	AbstractDFA(int noStates): states(new vector<int>()), tr(new map<pair<int*, char>, int*>()),current(start){
		initializeVector(noStates);
		start = &(*states)[0];
		final = &(*states)[noStates-1];
		sink = &(*states)[noStates];
	};
	~AbstractDFA() {
		delete current;
		delete final;
		delete sink;
		delete start;
		states->clear();
		tr->clear();
		states->~vector();
		tr->~map();
		delete states;
		delete tr;
	}

	/**
	 * Reset the automaton to the initial state.
	 */
	void reset() {
		current = start;
	}

	/**
	 * Performs one step of the DFA for a given letter. If there is a transition
	 * for the given letter, then the automaton proceeds to the successor state.
	 * Otherwise it goes to the sink state. By construction it will stay in the
	 * sink for every input letter.
	 * 
	 * @param letter
	 *            The current input.
	 */
	virtual void doStep(char letter) {
        bool found = false;
        for(map<pair<int*, char>, int*>::iterator it=tr->begin(); it!=tr->end(); ++it) {
            if(it->first == pair<int*,char>(current, letter)) {
                current = it->second;
                found = true;
            }
        }
		if(!found)
			current = sink;
    }
	
	/**
	 * Check if the automaton is currently accepting.
	 * 
	 * @return True, if the automaton is currently in the accepting state.
	 */
	bool isAccepting() {
		if(current==final) 
			return true;
		else return false;
	}

	/**
	 * Run the DFA on the input.
	 * 
	 * @param inputWord
	 *            stream that contains the input word
	 * @return True, if if the word is accepted by this automaton
	 */
	bool run(const string &inputWord) {
        this->reset();
        for(int i = 0; i < inputWord.length(); i++) {
            doStep(inputWord[i]);
        }
        return isAccepting();
}
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
	/* chiedere per il sink state unico*/
	
	 WordDFA(const string &word): AbstractDFA(word.length() +1){
		 for(int i =0;i<word.length();i++) {
			 tr->insert({pair<int*, char>(&(*states)[i],word[i]), &(*states)[i+1]});
		 }
	 }
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
	CommentDFA():AbstractDFA(8){ //6  per commento inline e 3 per commento multiline
		defineTransaction(start,'/',&(*states)[1]);
		// mancano for q1 e q0
		defineTransaction(&(*states)[1],'/',&(*states)[2]);
		for(int i = 0; i<255; i++) {
			if(i!=92)
				defineTransaction(&(*states)[2],i,&(*states)[2]);
		}
		defineTransaction(&(*states)[2],'/',&(*states)[3]);
		for(int i = 0; i<255; i++) {
			if(i!=110)
				defineTransaction(&(*states)[3],i,sink);
		}
		defineTransaction(&(*states)[3],'n',&(*states)[6]);
		defineTransaction(&(*states)[1],'*',&(*states)[4]);
		for(int i = 0; i<255; i++) {
			if(i!=42)
				defineTransaction(&(*states)[4],i,&(*states)[4]);
		}
		defineTransaction(&(*states)[4],'*',&(*states)[5]);
		defineTransaction(&(*states)[5],'*',&(*states)[5]);
		for(int i = 0; i<255; i++) {
			if(i!=42)
				defineTransaction(&(*states)[5],i,&(*states)[4]);
		}
		
	}; 
	
	/**
	 * Performs one step of the DFA for a given letter. This method works
	 * differently than in the superclass AbstractDFA.
	 * 
	 * @param letter
	 *            The current input.
	 */
    virtual void doStep(char letter) { 
		tr->insert(<pai)
	};
};