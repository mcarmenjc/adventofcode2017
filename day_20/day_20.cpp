#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

struct Particle {
    std::vector<int> position;
    std::vector<int> velocity;
    std::vector<int> acceleration;
    int id;
};

std::vector<int> GetPointFromString(std::string line, int start_pos = 0){
    int start = line.find('<', start_pos) + 1;
    int end = line.find('>', start_pos);
    std::string point = line.substr(start, end - start);
    std::vector<int> coord(3, 0);
    int comma = point.find(',');
    coord[0] = std::stoi(point.substr(0, comma));
    coord[1] = std::stoi(point.substr(comma+1, point.find(',', comma+1)));
    coord[2] = std::stoi(point.substr(point.find(',', comma+1)+1));

    return coord;
}

std::vector<Particle> ReadParticlesInSystem(std::string filename){
    std::vector<Particle> particles;
    std::ifstream file (filename);
    std::string line;
    int id = 0;
    while (std::getline(file, line)){
        Particle p;
        p.position = GetPointFromString(line);
        int start = line.find('<');
        p.velocity = GetPointFromString(line, start+1);
        start = line.find('<', start+1);
        p.acceleration = GetPointFromString(line, start+1);
        p.id = id;
        particles.push_back(p);
        ++id;
    }
    file.close();
    return particles;
}

void PrintParticle(const Particle &p){
    std::cout << "pos = (" << p.position[0] << ", " << p.position[1] << ", " << p.position[2] << ")\tvelocity = (" << p.velocity[0] << ", " << p.velocity[1] << ", " << p.velocity[2] << ")\tacceleration = (" << p.acceleration[0] << ", " << p.acceleration[1] << ", " << p.acceleration[2] << ")" << std::endl;
}

int GetManhatanDistance(const std::vector<int> &p){
    return (abs(p[0]) + abs(p[1]) + abs(p[2]));
}

int GetParticleCloserToZeroInTheLongRun(const std::vector<Particle> &particles){
    int closer_id = 0;
    int closer_pos_distance = GetManhatanDistance(particles[0].position);
    int closer_vel_distance = GetManhatanDistance(particles[0].velocity);
    int closer_acc_distance = GetManhatanDistance(particles[0].acceleration);

    for (int i = 1; i < particles.size(); ++i){
        int pos_distance = GetManhatanDistance(particles[i].position);
        int vel_distance = GetManhatanDistance(particles[i].velocity);
        int acc_distance = GetManhatanDistance(particles[i].acceleration);
        if (acc_distance == closer_acc_distance){
            if (vel_distance == closer_vel_distance){
                if (pos_distance < closer_pos_distance){
                    closer_id = i;
                    closer_pos_distance = pos_distance;
                    closer_vel_distance = vel_distance;
                    closer_acc_distance = acc_distance;
                }
            }
            else if (vel_distance < closer_vel_distance){
                closer_id = i;
                closer_pos_distance = pos_distance;
                closer_vel_distance = vel_distance;
                closer_acc_distance = acc_distance;
            }
        }
        else if (acc_distance < closer_acc_distance){
            closer_id = i;
            closer_pos_distance = pos_distance;
            closer_vel_distance = vel_distance;
            closer_acc_distance = acc_distance;
        }
    }

    return closer_id;
}

std::string PositionArrayToString(const Particle &p){
    std::string sposition = std::to_string(p.position[0]) + "|" + std::to_string(p.position[1]) + "|" + std::to_string(p.position[2]);
    return sposition;
}

int Iterate(std::vector<Particle> & particles){
    std::unordered_map< std::string, int > collisions;
    for (Particle & p : particles){
        p.velocity[0] += p.acceleration[0];
        p.velocity[1] += p.acceleration[1];
        p.velocity[2] += p.acceleration[2];

        p.position[0] += p.velocity[0];
        p.position[1] += p.velocity[1];
        p.position[2] += p.velocity[2];

        std::string str_pos = PositionArrayToString(p);
        if (collisions.count(str_pos) == 0){
            collisions.insert(std::make_pair(str_pos, 0));
        }
        collisions.at(str_pos) += 1;
    }

    std::vector<Particle> left_particles;
    for (const Particle &p : particles){
        std::string str_pos = PositionArrayToString(p);
        if (collisions.at(str_pos) == 1){
            left_particles.push_back(p);
        }
    }

    particles = left_particles;

    int min_distance = INT_MAX;
    int id = 0;
    for (const Particle &p : particles){
        int distance = GetManhatanDistance(p.position);
        if (distance < min_distance){
            min_distance = distance;
            id = p.id;
        }
    }

    return id;
}

int GetCloserWithCollisions(std::vector<Particle> &particles){
    int min_id = -1;
    int num_min = 0;
    while (num_min < 500){
        int curr_min = Iterate(particles);
        if (min_id == curr_min){
            ++num_min;
        }
        else{
            min_id = curr_min;
            num_min = 1;
        }
    }

    return min_id;
}

int main(int argc, char **argv){
    if (argc != 2){
        std::cout << "Use of the program is: \n\t day_20 <filename>\n" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    std::vector<Particle> particles = ReadParticlesInSystem(filename);
    int particle_closer_to_zero = GetParticleCloserToZeroInTheLongRun(particles);
    std::cout << "Particle closer to zero = " << particle_closer_to_zero << std::endl;
    int particle_closer_to_zero_no_collision = GetCloserWithCollisions(particles);
    std::cout << "Particle closer to zero = " << particle_closer_to_zero_no_collision << std::endl;
}