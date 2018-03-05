#ifndef CONFIG_H
#define CONFIG_H

enum performance {bad, hard, good, easy};
#include <vector>

class Config{
public:
	Config();
	~Config();

	void saveConfig();
	void loadConfig();

	//setters
	void set_MAX_NEW_CARDS(int i);
	void set_MAX_REVIEWS(int i);
	void set_learning_intervals(int i, int j);

	//getters
	int get_MAX_NEW_CARDS(){ return MAX_NEW_CARDS_;};
	int get_MAX_REVIEWS(){ return MAX_REVIEWS_;};
	std::vector<int> get_learning_intervals(){ return learning_intervals_;};

	//std::string(){ return userPass;};
	int get_LEARN_RELEARN_STEPS(){ return LEARN_RELEARN_STEPS_;}

private:
	int MAX_NEW_CARDS_, MAX_REVIEWS_, LEARN_RELEARN_STEPS_ = 2;
	//std::string userPass;
	std::vector<int> learning_intervals_;
	};

extern Config config;

#endif //CONFIG_H