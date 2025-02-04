#include <iostream>
#include <string>
#include <regex>
#include <unordered_map>

std::string getCardFlag(const std::string& cardNumber) {
    if (cardNumber.empty()) {
        return "Número de cartão inválido";
    }

    std::unordered_map<std::string, std::string> cardPatterns = {
        {"^4[0-9]{15}$", "Visa"},
        {"^5[1-5][0-9]{14}$", "MasterCard"},
        {"^3[47][0-9]{13}$", "American Express"},
        {"^6(?:011|5[0-9]{2})[0-9]{12}$", "Discover"},
        {"^3(?:0[0-5]|[68][0-9])[0-9]{11}$", "Diners Club"},
        {"^(2014|2149)[0-9]{11}$", "EnRoute"},
        {"^(?:2131|1800|35[0-9]{3})[0-9]{11}$", "JCB"},
        {"^8699[0-9]{11}$", "Voyager"},
        {"^(606282|3841)[0-9]{10,11}$", "Hipercard"},
        {"^50[0-9]{14,17}$", "Aura"}
    };

    for (const auto& pattern : cardPatterns) {
        if (std::regex_match(cardNumber, std::regex(pattern.first))) {
            return pattern.second;
        }
    }

    return "Número de cartão inválido";
}

bool isValidCardNumber(const std::string& cardNumber) {
    int sum = 0;
    bool alternate = false;
    for (int i = cardNumber.length() - 1; i >= 0; --i) {
        int n = cardNumber[i] - '0';
        if (alternate) {
            n *= 2;
            if (n > 9) {
                n -= 9;
            }
        }
        sum += n;
        alternate = !alternate;
    }
    return (sum % 10 == 0);
}

int main() {
    std::string cardNumber;
    std::cout << "Entre o número do cartão: ";
    std::cin >> cardNumber;

    std::string cardFlag = getCardFlag(cardNumber);
    std::cout << "Bandeira do cartão: " << cardFlag << std::endl;

    if (isValidCardNumber(cardNumber)) {
        std::cout << "O número do cartão é válido." << std::endl;
    } else {
        std::cout << "O número do cartão é inválido." << std::endl;
    }

    return 0;
}