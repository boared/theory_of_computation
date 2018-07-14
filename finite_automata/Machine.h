#ifndef MACHINE_H
#define MACHINE_H

#include <set>

#include <State.h>
#include <TransitionFunction.h>

namespace machine {

    /**
     * Deterministic Finite Automaton.
     *
     * A DFA is a machine defined as:
     *  M = (Q, F, SIGMA, delta, q0) where:
     *      Q = finite set of states
     *      F = subset of Q containing the accept states
     *      SIGMA = finite set of alphabet symbols
     *      delta = transition function defined as:
     *          delta: Q x SIGMA --> Q
     *      q0 = initial state
     */
    class DFA {
        private:
            /**
             * Machine states
             */ 
            std::set<State> Q;

            /**
             * Accept states
             */
            std::set<State> F;

            /**
             * Initial state
             */
            State q0;

            /**
             * Transition function
             */
            TransitionFunction delta;

            /**
             * Represents the current state of the machine
             */
            State currentState;

            /**
             * Process the input symbol calling the transition function with the current state.
             */
            void process(const std::string& symbol) {
                const State nextState = delta.compute(currentState, symbol);
                std::cout << "<" << currentState.getName() << "," << symbol << "> --> " << nextState.getName() << "\n";
                currentState = nextState;
            }

        public:
            DFA(const std::set<State>& Q,
                const std::set<State>& F,
                const State& q0,
                const TransitionFunction& delta) :
                Q(Q),
                F(F),
                q0(q0),
                delta(delta),
                currentState(q0.getName())
            {
            }

            /**
             * Given a word as input, verify if it's accepted by the machine or not.
             */
            bool accepts(const std::string& word) {
                currentState = q0;

                std::cout << "\nComputing [" << word << "]:\n";
                for (int i = 0; i < word.size(); i++) {
                    // The automaton process one symbol at a time
                    const std::string symbol = word.substr(i, 1);

                    // Process the symbol
                    process(symbol);
                }
                std::cout << "\n";

                // After processing all the symbols, if the current
                // state is in F, then the machine accepts the word
                return F.find(currentState) != F.end();
            }
    };
}
#endif

