#pragma once
#include <string>
class Exception
{
private:
	std::string message;
public:
	Exception(std::string message) : message(message) {} // constructor 
	const std::string& getMessage() const noexcept {
		return message;
	}
};
class ValidationException : public Exception { // mosteneste din exception
public:
	ValidationException(std::string message) : Exception(message) {};
};

class RepoException : public Exception { // mosteneste din exception
public:
	RepoException(std::string message) : Exception(message) {};
};

class UndoException :public Exception {
public:
	UndoException(std::string message) : Exception(message) {};
};