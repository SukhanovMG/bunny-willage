#pragma once

#include <iostream>
#include <string>
#include <random>

namespace bv {
	enum class Sex { Male, Female };
	enum class Color { White, Brown, Black, Spotted };

	std::string sex_to_string(bv::Sex sex)
	{
		switch (sex) {
			case bv::Sex::Male:
				return "Male";
			case bv::Sex::Female:
			default:
				return "Female";
		}
	}

	std::string color_to_string(bv::Color color)
	{
		switch (color) {
			case bv::Color::White:
				return "White";
			case bv::Color::Brown:
				return "Brown";
			case bv::Color::Black:
				return "Black";
			case bv::Color::Spotted:
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
			bv::Sex gen_sex() { return bv::Sex(dist_sex(gen)); }
			// even chance of each color
			bv::Color gen_color() { return bv::Color(dist_color(gen)); }
			// 2% chance of being radioactive mutant vampire
			bool gen_mutant() { return dist_mutant(gen) > 1 ? false : true; }

			// bunny properties
			bv::Sex   sex;
			bv::Color color;
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

			Bunny(bv::Color c) : Bunny()
			{
				color = c;
			}

			bv::Sex   get_sex()   const { return sex;   }
			bv::Color get_color() const { return color; }
			unsigned int get_age()   const { return age;   }
			std::string  get_name()  const { return name;  }

			bool is_mutant() const { return radioactive_mutant_vampire; }
			bool is_dead() const { return radioactive_mutant_vampire ? age > 50 : age > 10; }
	};

	std::ostream& operator<<(std::ostream& os, const bv::Bunny& b)
	{
		os << b.get_name() << ": " << color_to_string(b.get_color());
		os << " " << sex_to_string(b.get_sex());
		os << " " << b.get_age() << "yo";
		os << (b.is_mutant() ? " M" : "");
		return os;
	}
}