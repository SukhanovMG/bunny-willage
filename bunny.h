#pragma once

#include <iostream>
#include <string>
#include <random>

namespace bunny {
	enum class Sex { Male, Female };
	enum class Color { White, Brown, Black, Spotted };

	std::string sex_to_string(bunny::Sex sex)
	{
		switch (sex) {
			case bunny::Sex::Male:
				return "Male";
			case bunny::Sex::Female:
			default:
				return "Female";
		}
	}

	std::string color_to_string(bunny::Color color)
	{
		switch (color) {
			case bunny::Color::White:
				return "White";
			case bunny::Color::Brown:
				return "Brown";
			case bunny::Color::Black:
				return "Black";
			case bunny::Color::Spotted:
			default:
				return "Spotted";
		}
	}

	class Bunny
	{
		private:
			// randomization
			std::random_device seed;
			std::mt19937 gen;
			std::uniform_int_distribution<unsigned int> dist_sex;
			std::uniform_int_distribution<unsigned int> dist_color;
			std::uniform_int_distribution<unsigned int> dist_mutant;

			// 50% chance of sex
			bunny::Sex gen_sex() { return bunny::Sex(dist_sex(gen)); }
			// even chance of each color
			bunny::Color gen_color() { return bunny::Color(dist_color(gen)); }
			// 2% chance of being radioactive mutant vampire
			bool gen_mutant() { return dist_mutant(gen) > 1 ? false : true; }

			// bunny properties
			bunny::Sex   sex;
			bunny::Color color;
			unsigned int age;
			std::string  name;
			bool          radioactive_mutant_vampire;

		public:
			Bunny():
				gen(seed()), dist_sex(0, 1), dist_color(0, 3), dist_mutant(0, 99),
				sex(gen_sex()),
				color(gen_color()),
				age(0),
				name("Dummy"),
				radioactive_mutant_vampire(gen_mutant())
			{}

			Bunny(bunny::Color c) : Bunny()
			{
				color = c;
			}

			bunny::Sex   get_sex()   const { return sex;   }
			bunny::Color get_color() const { return color; }
			unsigned int get_age()   const { return age;   }
			std::string  get_name()  const { return name;  }

			bool is_mutant() const { return radioactive_mutant_vampire; }
			bool is_dead() const { return radioactive_mutant_vampire ? age > 50 : age > 10; }
	};

	std::ostream& operator<<(std::ostream& os, const bunny::Bunny& b)
	{
		os << b.get_name() << ": " << color_to_string(b.get_color());
		os << " " << sex_to_string(b.get_sex());
		os << " " << b.get_age() << "yo";
		os << (b.is_mutant() ? " M" : "");
		return os;
	}
}