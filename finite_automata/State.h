#ifndef STATE_H
#define STATE_H

#include <string>

class State {
    private:
        std::string name;

    public:
        State() : name("") {}
        State(const std::string& name) : name(name) {}

        bool operator==(const State& state) const {
            return name == state.name;
        }

        bool operator<(const State& state) const {
            return name < state.name;
        }

        bool operator>(const State& state) const {
            return name > state.name;
        }

        std::string getName() const {
            return name;
        }
};
#endif

