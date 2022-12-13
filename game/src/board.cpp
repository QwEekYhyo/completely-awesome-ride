#include <board.hpp>

board::board() {
    for (auto& row : m_grid) {
        for (auto& cell : row) {
            cell = player::none;
        }
    }
    m_current_player = player::one;
}

void board::switch_player() {
    m_current_player = m_current_player == player::one ? player::two : player::one;
}

bool board::is_column_full(int column) const {
    return at({column, 0}) != player::none;
}

int board::get_upper(int column) const {
    // we assume that this is called on a non-full column
    for (int i = height - 1; i >= 0; i--) {
        if (at({column, i}) == player::none) {
            return i;
        }
    }
    return 69; // compiler is crying because it might return void but in
               // reality it cannot
}

bool board::is_full() const {
    for (int i = 0; i < width; i++) {
        if (!is_column_full(i)) {
            return false;
        }
    }
    return true;
}

void board::play(int column) {
    if (!is_column_full(column)) {
        int top = get_upper(column);
        at({column, top}) = m_current_player;
        switch_player();
        m_last_position_played = std::make_pair(column, top);
    }
}

player& board::at(std::pair<int, int> coord) {
    return m_grid.at(coord.second).at(coord.first);
}

const player& board::at(std::pair<int, int> coord) const {
    return m_grid.at(coord.second).at(coord.first);
}

player board::get_winner_from_arr(const std::array<std::pair<int, int>, 4> &coords) const {
    player current_player;
    player next_player;
    for (int i = 0; i < coords.size() - 1; i++) {
        current_player = at({coords[i].first, coords[i].second});
        next_player = at({coords[i+1].first, coords[i+1].second});
        if (current_player == player::none || current_player != next_player) {
            return player::none;
        }
    }
    return current_player;
}

std::ostream& operator<<(std::ostream& os, const board& b) {
    for (int i = 0; i < b.height; i++) {
        for (int j = 0; j < b.width; j++) {
            if (b.at({j, i}) == player::one) {
                os << 'Y';
            } else if (b.at({j, i}) == player::two) {
                os << 'R';
            } else {
                os << '0';
            }
            os << ' ';
        }
        os << '\n';
    }
    return os;
}
