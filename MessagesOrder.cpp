// MessagesOrder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <random>

using namespace std;

class Message {
public:
	Message() = default;

	Message(string text, int number)
	{
		this->text = text;
		this->number = number;
	}

	const string& get_text() {
		return text;
	}

	const int get_number() {
		return number;
	}

	bool operator<(Message& that)
	{
		return this->number < that.get_number();
	}

private:
	string text;
	int number;
};

class MessageFactory {
public:
	MessageFactory() 
	{
		number = 1;
	}

	Message create_message(const string& text) {
		return {text, number++};
	}

private:
	int number;
};

class Recipient {
public:
	Recipient() = default;
	void receive(const Message& msg) {
		messages_.push_back(msg);
	}
	void print_messages() {
		fix_order();
		for (auto& msg : messages_) {
			cout << msg.get_text() << endl;
		}
		messages_.clear();
	}
private:
	void fix_order() {
		sort(messages_.begin(), messages_.end());
	}
	vector<Message> messages_;
};

class Network {
public:
	static void send_messages(vector<Message> messages, Recipient& recipient) {
		// simulates the unpredictable network, where sent messages might arrive in unspecified order
		shuffle(messages.begin(), messages.end(), std::mt19937(std::random_device()()));
		for (const auto& msg : messages) {
			recipient.receive(msg);
		}
	}
};

int main() {
	MessageFactory message_factory;
	Recipient recipient;
	vector<Message> messages;
	string text;
	int number = 1;
	while (number < 5 && getline(cin, text)) {
		number++;
		messages.push_back(message_factory.create_message(text));
	}
	Network::send_messages(messages, recipient);
	recipient.print_messages();
}
