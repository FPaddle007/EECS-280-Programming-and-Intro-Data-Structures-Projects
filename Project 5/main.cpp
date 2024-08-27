// Project UID db1f506d06d84ab787baf250c265e24e
// main.cpp

#include <map>
#include <set>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <iterator>
#include "csvstream.h"
#include <cassert>
#include <limits>
using namespace std;

set<string> unique_words(const string &str);

class Classifier {
 public:
  /* TO DO:
   * Make constructor(s), destructor (Do I need to make these?)
   */
  Classifier()
    : num_training_posts(0), num_test_posts(0), num_correct_predictions(0) {}
  
  //Reads contents from training .csv file and updates member variables
  bool train(string training_file, bool debug_mode) { 
    try {
      csvstream csvin(training_file);
      map<string, string> row;

      if (debug_mode) {
        cout << "training data:" << endl;
      }

      while (csvin >> row) {           
        string label = row["tag"];
        string raw_content = row["content"];

        if (debug_mode) {
          cout << "  label = " << label << ", content = " << raw_content << endl;
        }

        set<string> content = unique_words(raw_content);

        label_freq[label]++;
        ++num_training_posts;

        for (const auto &word : content) {  
          word_freq[word]++;
          label_map[label][word]++;
        }
      }
    } catch(const csvstream_exception &e) {
      cout << e.what() << endl;
      return true;
    }

    cout << "trained on " << num_training_posts << " examples" << endl;
    if (debug_mode) {
      cout << "vocabulary size = " << word_freq.size() << endl;
    }
    cout << endl;
    if (debug_mode) {
      cout << "classes:" << endl;
      
      for (const auto &element : label_freq) {
        cout << "  " << element.first << ", " << element.second << " examples, ";
        cout << "log-prior = " << log(static_cast<double>(label_freq[element.first]) 
        / num_training_posts) << endl; //might need to cast and do division
      }

      cout << "classifier parameters:" << endl;

      for (const auto &element : label_map) {
        for (const auto &pair : label_map[element.first]) {
          cout << "  " << element.first << ":";
          cout << pair.first << ", count = " << pair.second 
          << ", log-likelihood = ";
          cout << log(static_cast<double>(pair.second) / label_freq[element.first]) 
          << endl;
        }
      }

      cout << endl;
    }

    return false;
  }
  
  //Reads contents from testing .csv file and predicts the post's label
  bool predict(string test_file, bool debug_mode) {
    try {
      csvstream csvin(test_file);
      map<string, string> row;

      cout << "test data:" << endl;

      while (csvin >> row) {
        string label = row["tag"];
        string raw_content = row["content"];
        set<string> content = unique_words(raw_content);

        ++num_test_posts;

        string best_label_prediction = (*label_freq.begin()).first;
        double best_log_prob_score = -1 * numeric_limits<double>::infinity();

        //Calculate log probability of post for each tag and choose the highest
        for (const auto &element : label_freq) {
          string current_tag = element.first; 

          //Initial value of log probability score is P(C)
          double current_log_prob_score = log(static_cast<double>
          (label_freq[current_tag]) / num_training_posts);
        
          //Adding conditional probabilities associated with each word in post to
          //temporary log probability score.
          for (const auto &word : content) {
            if (label_map[current_tag].find(word) != label_map[current_tag].end()) {
              current_log_prob_score += 
              log(static_cast<double>(label_map[current_tag][word]) / 
                label_freq[current_tag]);
            } else if (word_freq.find(word) != word_freq.end()) {
              current_log_prob_score += log(static_cast<double>(word_freq[word])
                / num_training_posts);
            } else {
              current_log_prob_score += -log(num_training_posts);
            }
          }

          if (current_log_prob_score > best_log_prob_score) {
            best_log_prob_score = current_log_prob_score;
            best_label_prediction = current_tag;
          }
        }

        cout << "  correct = " << label << ", predicted = " << best_label_prediction;
        cout << ", log-probability score = " << best_log_prob_score << endl;
        cout << "  content = " << raw_content << endl;
        cout << endl;

        if (label == best_label_prediction) {
          ++num_correct_predictions;
        } 
      }
    } catch(const csvstream_exception &e) {
      cout << e.what() << endl;
      return true;
    }
    cout << "performance: " << num_correct_predictions << " / " << num_test_posts;
    cout << " posts predicted correctly\n";

    return false;
  }

 private:

 //"Frequency" refers to the number of posts in the training set with 
 //the given attributes.
 
  map<string, int> word_freq;
  map<string, int> label_freq;
  map<string, map<string, int>> label_map; //map component: map<word, frequency>
  int num_training_posts;
  int num_test_posts;
  int num_correct_predictions;
};

// EFFECTS: Returns a set containing the unique "words" in the original
//          string, delimited by whitespace.
set<string> unique_words(const string &str) {
 istringstream source{str};
 return {istream_iterator<string>{source},
         istream_iterator<string>{}};
}


int main(int argc, char** argv) {

  //Check argc to make ensure proper number of arguments and
  //that --debug argument is properly used if included.
  if ((argc != 3 && argc != 4) || (argc == 4 && strcmp(argv[3], "--debug"))) {
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    return 1;
  }

  //Convert argv cstring corresponding to file input into a string
  string training_file = argv[1];
  string test_file = argv[2];

  bool debug_mode = false;
  if (argc == 4) {
    debug_mode = true;
  }

  cout.precision(3);

  Classifier classifier;
  
  bool training_error_encountered = classifier.train(training_file, debug_mode);

  if (training_error_encountered) {
    return 1;
  }

  bool testing_error_encountered = classifier.predict(test_file, debug_mode);

  if (testing_error_encountered) {
    return 1;
  }
  return 0;
}