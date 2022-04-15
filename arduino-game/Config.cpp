#include "Config.h"

Config::Config() {
  EEPROM.begin(CONF_EEPROM_SIZE);
}

void Config::read() {
  this->scoreboardIP = this->readString(CONF_SB_IP_ADDR, CONF_SB_IP_LEN);
  this->numPlayers = this->readByte(CONF_NPLAYERS_ADDR);

  // Validation
  this->scoreboardIP.trim();
  if (this->numPlayers < MIN_PLAYERS) {
    this->numPlayers = MIN_PLAYERS;
  } else if (this->numPlayers > MAX_PLAYERS) {
    this->numPlayers = MAX_PLAYERS;
  }

  // Debug
  Serial.print("Scoreboard IP: ");
  Serial.println(this->scoreboardIP);
  Serial.print("Num players: ");
  Serial.println(this->numPlayers);
}

void Config::write() {
  // Truncate/pad scoreboard IP
  String sbIP = this->scoreboardIP;
  if (sbIP.length() > CONF_SB_IP_LEN) {
    sbIP = "";
    for (int i = 0; i < CONF_SB_IP_LEN; i++) {
      sbIP += this->scoreboardIP[i];
    }
  } else if (sbIP.length() < CONF_SB_IP_LEN) {
    while (sbIP.length() < CONF_SB_IP_LEN) {
      sbIP += " "; // add a space
    }
  }

  this->writeString(CONF_SB_IP_ADDR, sbIP);
  this->writeByte(CONF_NPLAYERS_ADDR, byte(this->numPlayers));
  this->read(); // read back for validation
}

void Config::clear() {
  this->scoreboardIP = "";
  this->numPlayers = 0;
  this->write();
}

String Config::readString(int addr, int len) {
  String val = "";
  for (int i = 0; i < len; i++) {
    val += char(EEPROM.read(addr + i));
  }
  return val;
}

void Config::writeString(int addr, String val) {
  for (int i = 0; i < val.length(); i++) {
    EEPROM.write(addr + i, val[i]);
  }
}

int Config::readInt(int addr) {
  byte part1 = EEPROM.read(addr);
  byte part2 = EEPROM.read(addr + 1);

  return (part1 << 8) + part2;
}

void Config::writeInt(int addr, int val) {
  EEPROM.write(addr, val >> 8);
  EEPROM.write(addr + 1, val & 0xFF);
}

byte Config::readByte(int addr) {
  return EEPROM.read(addr);
}

void Config::writeByte(int addr, byte val) {
  EEPROM.write(addr, val);
}