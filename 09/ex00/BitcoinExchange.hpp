#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
private:
    std::map<std::string, double> _prices;

    static std::string trim(const std::string &s);
    static bool isValidDate(const std::string &date);
    static bool isLeapYear(int year);
    static bool parseValue(const std::string &s, double &value);

    double getPriceForDate(const std::string &date) const;

public:
    BitcoinExchange(void);
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange(void);

    void loadDatabase(const std::string &filename);
    void processInput(const std::string &filename) const;
};

#endif