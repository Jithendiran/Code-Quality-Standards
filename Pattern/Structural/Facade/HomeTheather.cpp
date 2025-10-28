/*
 * Programmer: E.K.Jithendiran
 * Date: 27 Oct 2025
 */
// g++ -o /tmp/HomeTheather HomeTheather.cpp

/*
Projecter, Amplifier and DVDPlayer each are different subsystems,these all has to communicte in sync with each other to watch a move, It may be pain full to operate each in seperate (To on, off, pause/play,..), so we are going to create a HomeTheather facade which will handle those internals
*/


#include <iostream>
#include <string>

// --- Subsystem 1: Projector ---
class Projector {
public:
    void on() const { std::cout << "Projector is ON\n"; }
    void off() const { std::cout << "Projector is OFF\n"; }
    void setInput(const std::string& source) const { 
        std::cout << "Projector input set to: " << source << "\n"; 
    }
};

// --- Subsystem 2: Amplifier ---
class Amplifier {
public:
    void on() const { std::cout << "Amplifier is ON\n"; }
    void off() const { std::cout << "Amplifier is OFF\n"; }
    void setVolume(int level) const { 
        std::cout << "Amplifier volume set to " << level << "\n"; 
    }
    void setSurroundSound() const { std::cout << "Amplifier set to surround sound mode\n"; }
};

// --- Subsystem 3: DVDPlayer ---
class DVDPlayer {
public:
    void on() const { std::cout << "DVD Player is ON\n"; }
    void off() const { std::cout << "DVD Player is OFF\n"; }
    void play(const std::string& movie) const { 
        std::cout << "DVD Player is playing \"" << movie << "\"\n"; 
    }
    void stop() const { std::cout << "DVD Player has stopped\n"; }
};

// --- The Facade: HomeTheaterFacade ---
class HomeTheaterFacade {
private:
    // References to the subsystem objects (composition)
    Projector projector;
    Amplifier amplifier;
    DVDPlayer dvdPlayer;

public:
    // Constructor (initializes the subsystems)
    HomeTheaterFacade() {}

    // Simplified method 1
    void watchMovie(const std::string& movieName) {
        std::cout << "\nGet ready to watch a movie...\n";
        
        // Complex, ordered sequence of calls delegated to subsystems
        dvdPlayer.on();

        projector.on();
        projector.setInput("DVD");

        amplifier.on();
        amplifier.setSurroundSound();
        amplifier.setVolume(20);

        dvdPlayer.play(movieName);
    }

    // Simplified method 2:
    void endMovie() {
        std::cout << "\n Shutting down the home theater...\n";
        
        // Complex, ordered sequence of calls delegated to subsystems
        dvdPlayer.stop();
        dvdPlayer.off();

        amplifier.off();
        projector.off();
    }
};

// --- Client Code (main function) ---
int main() {
    // Client creates the Facade instance
    HomeTheaterFacade theater;

    // Client only makes ONE high-level call to start the whole process
    theater.watchMovie("Inception");

    std::cout << "\n-- Movie is running --\n";

    // Client only makes ONE high-level call to stop the whole process
    theater.endMovie();

    return 0;
}