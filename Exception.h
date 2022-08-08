#pragma once
#include <exception>

class Exception : public std::exception {
public:
  Exception() = default;
  Exception(const std::string &msg) : _what(msg) {}

  Exception(const Exception &) = default;
  Exception &operator=(const Exception &) = default;
  Exception(Exception &&) = default;
  Exception &operator=(Exception &&) = default;

  virtual ~Exception() noexcept override = default;

  virtual const char *what() const noexcept override {
    return _what.empty() ? "Unknown exception" : _what.c_str();
  }

protected:
  std::string _what;
};