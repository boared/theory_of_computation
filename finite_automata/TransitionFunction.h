#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include <map>
#include "State.h"

/**
 * Maps a pair <State, symbol> to a State
 */
class TransitionFunction {
    private:
        std::map<std::pair<State, std::string>, State> mapping;

    public:
        void addTransition(const State& stateDomain, const std::string& symbolDomain, const State& stateRange) {
            mapping[std::make_pair(stateDomain, symbolDomain)] = stateRange;
        }

        State compute(const State& state, const std::string& symbol) {
            return mapping[std::make_pair(state, symbol)];
        }
};
#endif

