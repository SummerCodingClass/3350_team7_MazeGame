// Created by: Eidmone Tagaca
// Source File for Project 3350

#include <iostream>
#include "fonts.h"
#include <iostream>
#include "GridCells.h"

using namespace std;

void et_PrintMsg() {
    cout << "Eidmone's file fired" <<endl;
}

void et_showCreditPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Eidmone Tagaca: ");
  ggprint8b(&position, 16, color, "Game Designer | Game Developer");
}

void et_showRulesPage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  ggprint8b(&position, 16, color, "Rule 4:");
  ggprint8b(&position, 16, color, "Once you exit the game, progress will NOT be saved.");
}

void et_showWelcomePage(Rect position, int defaultHeight, int color) {
  position.bot = defaultHeight;
  
  ggprint8b(&position, 16, color, "press 'C' to view credit page");
}

bool GridCells::setWall(bool input) {
  wall = input;
  return wall;
}

bool GridCells::setStart(bool input) {
  start = input;
  return start;
}

bool GridCells::setEnd(bool input) {
  end = input;
  return end;
}

// ===> Added function for the midterm <===
// Info: receives a string input and outputs it to terminal
void etagaca(string name) {
  // If the input name is an empty string
  // then we display error to terminal
  if (name == "") {
    cout << "Error please enter a name!" << endl;
  } else {
    // If the input is valid then output this
    cout << name << " is awesome!";
  }
}

