void link_grid(vector<vector<Cell>>& board, int size){
    //link neigbors one direction at a time
    for (int dir = Cell::up; dir <= Cell::up_left; dir++){
        //loop through all cells
        for (int y = 0; y < size; y++){
            for (int x = 0; x < size; x++){
                //coordinates of the neighbor cell
                int x2 = x;
                int y2 = y;
                switch (dir){
                    case Cell::up:
                        y2 = y - 1;
                        break;
                    case Cell::up_right:
                        y2 = y - 1;
                        x2 = x + 1;
                        break;
                    case Cell::right:
                        x2 = x + 1;
                        break;
                    case Cell::down_right:
                        y2 = y + 1;
                        x2 = x + 1;
                        break;
                    case Cell::down:
                        y2 = y + 1;
                        break;
                    case Cell::down_left:
                        y2 = y + 1;
                        x2 = x - 1;
                        break;
                    case Cell::left:
                        x2 = x - 1;
                        break;
                    case Cell::up_left:
                        y2 = y - 1;
                        x2 = x - 1;
                        break;
                    default:
                        break;
                }
                //ignore coordinates not in the grid
                if (y2 < 0 || y2 >= size || x2 < 0 || x2 >= size){
                    continue;
                }
                board.at(y).at(x).link(static_cast<Cell::Direction>(dir), board.at(y2).at(x2));
            }
        }
    }
}



int count_chain(Cell& start, Cell::Direction direction, int value){
    Cell::Direction opposite = static_cast<Cell::Direction>((direction + 4) % 8);
    int chain = 1;
    Cell* current = start.next(direction);

    while(current != nullptr){
        if (current->get_value() != value){
            break;
        }
        chain++;
        current = current->next(direction);
    }
    //check in the opposite direction
    current = start.next(opposite);
    while(current != nullptr){
        if (current->get_value() != value){
            break;
        }
        chain++;
        current = current->next(opposite);
    }
    return chain;
}
