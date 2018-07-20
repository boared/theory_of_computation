#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include <map>
#include <set>
#include "State.h"

/**
 * Maps a pair<State, symbol> to a set<State>
 */
class TransitionFunction {
    private:
        std::map<std::pair<State, std::string>, std::set<State>> _mapping;

    public:
        void addTransition(const State& stateDomain, const std::string& symbolDomain, const State& stateRange) {
            _mapping[std::make_pair(stateDomain, symbolDomain)].insert(stateRange);
        }

        std::set<State> mapping(const State& state, const std::string& symbol) {
            const auto& x = std::make_pair(state, symbol);
            if (_mapping.find(x) != _mapping.end()) {
                return _mapping[x];
            } else {
                return std::set<State>();
            }
        }
};
#endif

