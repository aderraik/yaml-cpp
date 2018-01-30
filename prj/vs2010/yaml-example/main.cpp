#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// our data types
struct Vec3 {
   float x, y, z;
};

struct Power {
   std::string name;
   int damage;
};

struct Monster {
   std::string name;
   Vec3 position;
   std::vector <Power> powers;
};

/***
 * INPUT
 */
// now the extraction operators for these types
void operator >> (const YAML::Node& node, Vec3& v) {
   node[0] >> v.x;
   node[1] >> v.y;
   node[2] >> v.z;
}

void operator >> (const YAML::Node& node, Power& power) {
   node["name"] >> power.name;
   node["damage"] >> power.damage;
}

void operator >> (const YAML::Node& node, Monster& monster) {
   node["name"] >> monster.name;
   node["position"] >> monster.position;
   const YAML::Node& powers = node["powers"];
   for(unsigned i=0;i<powers.size();i++)
   {
      Power power;
      powers[i] >> power;
      monster.powers.push_back(power);
   }
}

/***
 * OUTPUT
 */
YAML::Emitter& operator << (YAML::Emitter& out, const Vec3& v) {
	out << YAML::Flow;
	out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
	return out;
}

YAML::Emitter& operator << (YAML::Emitter& out, const Power& power) {
	out << YAML::BeginMap;
   out << YAML::Key << "name" << YAML::Value << power.name;
   out << YAML::Key << "damage" << YAML::Value << power.damage;
	out << YAML::EndMap;
	return out;
}

YAML::Emitter& operator << (YAML::Emitter& out, const Monster& monster) {
   out << YAML::BeginMap;
   out << YAML::Key << "name" << YAML::Value << monster.name;
   out << YAML::Key << "position" << YAML::Value << monster.position;
   out << YAML::Key << "powers" << YAML::Value << monster.powers;
	out << YAML::EndMap;
	return out;
}

int main()
{
   YAML::Emitter out;

   std::ifstream fin("monsters.yaml");
   YAML::Parser parser(fin);
   YAML::Node doc;
   parser.GetNextDocument(doc);
	out << YAML::BeginSeq;
   for(unsigned i=0;i<doc.size();i++)
   {
      Monster monster;
      doc[i] >> monster;
      std::cout << monster.name << "\n";
      out << monster;
   }
	out << YAML::EndSeq;

   std::cout << "Here's the output YAML:\n" << out.c_str();
   return 0;
}
