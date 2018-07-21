#ifndef MACHINE_H
#define MACHINE_H

#include <set>
#include <iostream>
#include <State.h>
#include <TransitionFunction.h>

namespace machine {

    /**
     * Non-deterministic Finite Automaton.
     *
     * A NFA is a machine defined as:
     *  M = (Q, ∑, δ, q0, F) where:
     *      Q = finite set of states
     *      ∑ = finite set of alphabet symbols
     *      δ = transition function defined as:
     *          δ: Q X {∑, ε} --> P(Q),
     *              where ε denotes the empty string - that means the transition is done
     *              but the next symbol is not read - and P(Q) is the power set of Q.
     *      q0 = initial state
     *      F = subset of Q containing the accept states
     * 
     * This machine can simulate a Deterministic Finite Automaton as well as DFAs are a
     * subset of NFA.
     */
    class NFA {
        private:
            /**
             * Represents an empty word in a transition step
             */
            const std::string EMPTY_WORD = "<eps>";
            
            /**
             * Used to align printed steps.
             */
            const std::string TAB = "  ";

            /**
             * Set of states
             */
            std::set<State> Q;

            /**
             * Transition function
             */
            TransitionFunction delta;

            /**
             * Initial state
             */
            State q0;

            /**
             * Accept states (a subset of Q)
             */
            std::set<State> F;

            /**
             * Verify if a given state is in F
             */
            bool isAcceptState(const State& state) {
                return F.find(state) != F.end();
            }

            /**
             * Executes the machine to verify if a word is accepted or not.
             */
            bool accept(const std::string& tab, const State& currentState, const std::string& word) {
                // Symbol to be evaluated
                std::string symbol;

                // Check if the current state has e-moves. That means we need to execute e-move branches without
                // reading the next symbol
                std::set<State> e_move_states = transition(tab, currentState, EMPTY_WORD);

                if (word.empty()) {
                    symbol = EMPTY_WORD;

                    // If there's no further data in input to be read and no e-moves, then
                    // verify if the word is accepted or not
                    if (e_move_states.empty()) {
                        return isAcceptState(currentState);
                    }
                } else {
                    symbol = word[0];
                }

                // Let's check which transitions we need to do
                std::set<State> states;
                if (symbol != EMPTY_WORD) {
                    states = transition(tab, currentState, symbol);
                }

                bool accept = false;

                // We're going to execute all transitions and e-moves now. Theorethically they run in parallel, but
                // we're executing them sequentially here for simplicity. If any replicated machine returns true, then
                // the machine accepts the word.

                // Let's execute the e-moves now. Notice that we pass the same input word to the accept method as we
                // will process the same head symbol in the e-move branch
                for (const State& state : e_move_states) {
                    NFA m(*this);
                    accept = m.accept(tab + "|" + TAB, state, word) || accept;
                }

                // Let's execute the transitions. Notice that we remove the symbol processed here for the further steps.
                for (const State& state : states) {
                    NFA m(*this);
                    accept = m.accept(tab + "|" + TAB, state, word.substr(1, std::string::npos)) || accept;
                }

                return accept;
            }

            /**
             * Given an state and a symbol returns the set of transition states
             */
            std::set<State> transition(const std::string& tab, const State& state, const std::string& symbol) {
                std::set<State> states = delta.mapping(state, symbol);

                if (!states.empty()) {
                    std::cout << tab << "<" << state.getName() << "," << symbol << "> --> ";
                    for (const auto& state : states) {
                        std::cout << state.getName() << " ";
                    }

                    std::cout << "\n";
                }

                return states;
            }

        public:
            NFA(const std::set<State>& Q,
                const TransitionFunction& delta,
                const State& q0,
                const std::set<State>& F) :
                Q(Q),
                delta(delta),
                q0(q0),
                F(F)
            {
            }

            NFA(const NFA& copy) : NFA(copy.Q, copy.delta, copy.q0, copy.F) { }

            /**
             * Given an input word, the machine returns true
             * if it accepts the word, false otherwise.
             */
            bool accept(const std::string& word) {
                std::cout << "***** Computing word [" << word << "] *****\n";

                bool status = accept("", q0, word);

                std::cout << "***** Word [" << word << "] is : " << (status? "accepted" : "rejected") << "! *****\n\n";

                return status;
            }
    };
}
#endif

