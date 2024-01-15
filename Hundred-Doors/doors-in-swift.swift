/*  _  ___   ___        _                      
   / |/ _ \ / _ \    __| | ___   ___  _ __ ___ 
   | | | | | | | |  / _` |/ _ \ / _ \| '__/ __|
   | | |_| | |_| | | (_| | (_) | (_) | |  \__ \
   |_|\___/ \___/   \__,_|\___/ \___/|_|  |___/   an example problem
                                            
   There are 100 doors in a row that are all initially closed.

   You make 100 passes by the doors.
   * The first time through, visit every door and toggle the door
     (i.e., if the door is closed, open it;  if it is open, close it).
   * The second time, only visit every 2nd door (door #2, #4, #6, ...),
     and toggle it.
   * The third time, visit every 3rd door (door #3, #6, #9, ...), etc,
   ... until you only visit the 100th door.

                        (original problem seen on rosettacode.org)
                        
   You can compile this code and make an executable (IF YOU HAVE SWIFT 
   INSTALLED) with:
   
       swiftc doors-in-swift.swift
       
   and then run the resulting executable with:
   
       ./doors-in-swift
 */

var isOpen = [Bool](repeating: false, count: 100)

for step in 1...100 {
    for door in stride(from: step-1, to: 100, by: step) {
        isOpen[door] = !isOpen[door];
    }
}

for i in 0..<100 {
    if (isOpen[i]) {
        print("Door \(i+1) is open")
    }
}
