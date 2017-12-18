#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Node {
    Node * next;
    int value;
};

std::list<int>::iterator GetPositionToInsertNewStep(std::list<int>::iterator &current_position, std::list<int> spinlock_steps, int distance){
    std::list<int>::iterator next_step_pos = current_position;
    for(int i = 0; i < distance; ++i){
        if (next_step_pos == spinlock_steps.end()){
            next_step_pos = spinlock_steps.begin();
        }
        else{
            ++next_step_pos;
        }
    }
    return next_step_pos == spinlock_steps.end() ? next_step_pos : ++next_step_pos;
}

void PrintList(Node *n){
    Node *it = n;
    while (it->next != n){
        std::cout << it->value << "\t";
        it = it->next;
    }
    std::cout << it->value << "\t" << std::endl;
}

std::pair<Node *, Node *> GetSpinlockSteps(int num_jumps, int distance){
    Node *head = new Node();
    head->value = 0;
    head->next = head;
    Node * it = head;

    for (int i = 1; i < num_jumps; ++i){
        for (int j = 0; j < distance; ++j){
            it = it->next;
        }
        Node * next_node = new Node();
        next_node->value = i;
        next_node->next = it->next;
        it->next = next_node;
        it = next_node;
    }

    return std::make_pair(head, it);
}

int main(int argc, char **argv){
    if (argc != 3){
        std::cout << "Use of the program is: \n\t day_17 <jumps> <distance>\n" << std::endl;
        return 0;
    }
    int jumps = stoi(argv[1]);
    int distance = stoi(argv[2]);
    
    std::pair<Node *, Node*> head_tail_list = GetSpinlockSteps(jumps, distance);
    std::cout << "Next number after " << jumps << " = " << head_tail_list.second->next->value << std::endl;
    std::cout << "Next number after 0 = " << head_tail_list.first->next->value << std::endl;
}