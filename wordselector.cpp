#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <random>
#include <stdexcept>
#include "wordselector.h"

std::pair<std::string, std::string> word_selector(int mode)
{
    std::vector<std::pair<std::string, std::string>> easy_mode_words = {
        {"apple", "A fruit that can be red or green"},
        {"bread", "A food made from flour"},
        {"chair", "You sit on this"},
        {"house", "A place where people live"},
        {"tiger", "A large wild cat with stripes"},
        {"pizza", "A round food with cheese and toppings"},
        {"water", "You drink this to stay hydrated"},
        {"smile", "You do this when you are happy"},
        {"plant", "A living thing that grows in soil"},
        {"cloud", "A white or gray thing floating in the sky"},
        {"beach", "A sandy place beside the sea"},
        {"clock", "It tells you the time"},
        {"spoon", "You use this to eat soup"},
        {"shoes", "You wear these on your feet"},
        {"grape", "A small fruit that grows in bunches"},
        {"lemon", "A yellow fruit that tastes sour"},
        {"rabbit", "A small animal with long ears"},
        {"monkey", "An animal that likes climbing trees"},
        {"school", "A place where students learn"},
        {"pencil", "You use this to write and draw"},
        {"window", "You can look outside through this"},
        {"garden", "A place where flowers and plants grow"},
        {"banana", "A long, yellow fruit"},
        {"orange", "A round citrus fruit"},
        {"cookie", "A sweet baked snack"},
        {"donkey", "A farm animal similar to a horse"},
        {"monkey", "An animal that can swing from branches"},
        {"kitten", "A baby cat"},
        {"puppy", "A baby dog"},
        {"turtle", "A slow animal with a hard shell"},
        {"pillow", "You rest your head on this when sleeping"},
        {"blanket", "You cover yourself with this to keep warm"},
        {"rocket", "A vehicle that can travel into space"},
        {"basket", "You use this to carry or hold things"},
        {"button", "You press this to operate something"},
        {"bottle", "A container used to hold liquids"},
        {"window", "An opening in a wall with glass"},
        {"yellow", "The color of the sun in children's drawings"},
        {"purple", "A color made by mixing red and blue"},
        {"school", "A place where children study"},
        {"doctor", "A person who treats sick people"},
        {"farmer", "A person who grows crops or raises animals"},
        {"driver", "A person who drives a vehicle"},
        {"soccer", "A sport played by kicking a ball"},
        {"tennis", "A sport played with rackets and a ball"},
        {"puzzle", "A game that makes you solve a problem"},
        {"rocket", "A machine used to travel into space"},
        {"island", "Land surrounded by water"},
        {"forest", "A large area covered with trees"},
        {"sunset", "When the sun disappears below the horizon"}};
    std::vector<std::pair<std::string, std::string>> medium_mode_words = {
        {"apple", "A fruit that can be red or green"},
        {"bread", "A food made from flour"},
        {"chair", "You sit on this"},
        {"house", "A place where people live"},
        {"tiger", "A large wild cat with stripes"},
        {"pizza", "A round food with cheese and toppings"},
        {"water", "You drink this to stay hydrated"},
        {"smile", "You do this when you are happy"},
        {"plant", "A living thing that grows in soil"},
        {"cloud", "A white or gray thing floating in the sky"},
        {"beach", "A sandy place beside the sea"},
        {"clock", "It tells you the time"},
        {"spoon", "You use this to eat soup"},
        {"shoes", "You wear these on your feet"},
        {"grape", "A small fruit that grows in bunches"},
        {"lemon", "A yellow fruit that tastes sour"},
        {"rabbit", "A small animal with long ears"},
        {"monkey", "An animal that likes climbing trees"},
        {"school", "A place where students learn"},
        {"pencil", "You use this to write and draw"},
        {"window", "You can look outside through this"},
        {"garden", "A place where flowers and plants grow"},
        {"banana", "A long, yellow fruit"},
        {"orange", "A round citrus fruit"},
        {"cookie", "A sweet baked snack"},
        {"donkey", "A farm animal similar to a horse"},
        {"monkey", "An animal that can swing from branches"},
        {"kitten", "A baby cat"},
        {"puppy", "A baby dog"},
        {"turtle", "A slow animal with a hard shell"},
        {"pillow", "You rest your head on this when sleeping"},
        {"blanket", "You cover yourself with this to keep warm"},
        {"rocket", "A vehicle that can travel into space"},
        {"basket", "You use this to carry or hold things"},
        {"button", "You press this to operate something"},
        {"bottle", "A container used to hold liquids"},
        {"window", "An opening in a wall with glass"},
        {"yellow", "The color of the sun in children's drawings"},
        {"purple", "A color made by mixing red and blue"},
        {"school", "A place where children study"},
        {"doctor", "A person who treats sick people"},
        {"farmer", "A person who grows crops or raises animals"},
        {"driver", "A person who drives a vehicle"},
        {"soccer", "A sport played by kicking a ball"},
        {"tennis", "A sport played with rackets and a ball"},
        {"puzzle", "A game that makes you solve a problem"},
        {"rocket", "A machine used to travel into space"},
        {"island", "Land surrounded by water"},
        {"forest", "A large area covered with trees"},
        {"sunset", "When the sun disappears below the horizon"}};

    std::vector<std::pair<std::string, std::string>> hard_mode_words = {
        {"labyrinth", "A complicated network of paths that is difficult to navigate"},
        {"pneumonia", "A lung infection that can make breathing difficult"},
        {"xylophone", "A musical instrument made of bars that you strike"},
        {"quarantine", "Isolation used to prevent the spread of disease"},
        {"phenomenon", "An observable event or occurrence"},
        {"architecture", "The art and science of designing buildings"},
        {"camouflage", "A way of hiding by blending into the surroundings"},
        {"kaleidoscope", "A tube that creates colorful patterns using mirrors"},
        {"consequence", "A result or effect of an action"},
        {"extraordinary", "Very unusual or remarkable"},
        {"mischievous", "Playfully causing trouble"},
        {"onomatopoeia", "A word that imitates a sound, such as buzz"},
        {"hierarchy", "A system in which people or things are ranked"},
        {"philosophy", "The study of fundamental questions about existence and knowledge"},
        {"bureaucracy", "A system of administration with many rules and procedures"},
        {"cryptocurrency", "Digital currency that uses cryptography"},
        {"juxtaposition", "The act of placing two things side by side for comparison"},
        {"entrepreneur", "A person who starts and runs a business"},
        {"conscientious", "Careful to do things correctly and responsibly"},
        {"idiosyncrasy", "A distinctive habit or characteristic of a person"},
        {"metamorphosis", "A major change in the form of an animal during development"},
        {"rendezvous", "A planned meeting at a particular time or place"},
        {"silhouette", "The dark outline of something seen against a lighter background"},
        {"belligerent", "Hostile and eager to argue or fight"},
        {"juxtapose", "To place two things together to compare them"},
        {"labyrinthine", "Extremely complicated, like a maze"},
        {"inconspicuous", "Not easily noticed or attracting attention"},
        {"surveillance", "Close observation of a person or place"},
        {"equilibrium", "A state of balance between opposing forces"},
        {"perseverance", "Continued effort despite difficulty"},
        {"obsolescence", "The state of becoming outdated or no longer useful"},
        {"reconnaissance", "The act of gathering information about an area"},
        {"acquiescence", "The act of accepting something without protest"},
        {"sesquipedalian", "Describing someone who uses long words"},
        {"circumstantial", "Based on indirect evidence or related details"},
        {"unprecedented", "Never having happened or existed before"},
        {"discombobulate", "To confuse or bewilder someone"},
        {"infrastructure", "The basic systems and facilities a society needs"},
        {"magnanimous", "Generous and forgiving, especially toward a rival"},
        {"ephemeral", "Lasting for only a short time"},
        {"cacophony", "A harsh mixture of unpleasant sounds"},
        {"vicissitude", "A change in circumstances, often an unpleasant one"},
        {"perspicacious", "Having a sharp ability to understand things"},
        {"anachronism", "Something placed in a time period where it does not belong"},
        {"floccinaucinihilipilification", "The act of considering something worthless"},
        {"antidisestablishmentarianism", "Opposition to removing an established church's official status"},
        {"supercalifragilisticexpialidocious", "A famously long, playful word expressing delight"},
        {"electroencephalogram", "A recording of the electrical activity of the brain"},
        {"otorhinolaryngology", "The medical specialty dealing with the ears, nose, and throat"},
        {"incomprehensibility", "The quality of being impossible or very difficult to understand"}
    };
    
    std::string hint;
    std::string word;

    if (mode == 1)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<std::size_t> dist(
            0, easy_mode_words.size() - 1
        );

        std::size_t index = dist(gen);

        word = easy_mode_words[index].first;
        hint = easy_mode_words[index].second;
    }
    else if (mode == 2)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<std::size_t> dist(
            0, medium_mode_words.size() - 1
        );

        std::size_t index = dist(gen);

        word = medium_mode_words[index].first;
        hint = medium_mode_words[index].second;
    }
    else if (mode == 3)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<std::size_t> dist(
            0, hard_mode_words.size() - 1
        );

        std::size_t index = dist(gen);

        word = hard_mode_words[index].first;
        hint = hard_mode_words[index].second;
    }
    else
    {
        throw std::invalid_argument("Invalid difficulty mode");
    }

    return {word, hint};
}
