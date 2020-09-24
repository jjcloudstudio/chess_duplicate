#include <iostream>

class Door {
public:
  virtual void lock(bool state){
    locked = state;
  }

  virtual std::string open(){
      if(locked == false)
        return "Door Opened";
      return "";
  }

  virtual std::string close(){
      return "Door Closed";
  }

private:
  bool locked;
};

class House {
public:
  House(Door* d) : door(d) {
    dogInHouse = true;
  }

  virtual void dogOut() {
    door->lock(false);
    door->open();
    dogInHouse = false;
    door->close();
    door->lock(true);
  }

  bool dogInside() {
    return dogInHouse;
  }

protected:
  bool dogInHouse;
  Door* door;
};

class House_WrongOrder : public House {
public:
  House_WrongOrder(Door* d) : House(d) { }

  virtual void dogOut() {
    door->lock(false);
    door->open();
    dogInHouse = false;
    door->lock(true);
    door->close();

  }
};

class House_MissingAction : public House {
public:
  House_MissingAction(Door* d) : House(d) { }

  virtual void dogOut() {
    //door->lock(false);
    door->open();
    dogInHouse = false;
    door->close();
    door->lock(true);
  }
};
