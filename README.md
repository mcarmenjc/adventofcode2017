# ADVENT OF CODE 2017

This year instead of eating a chocolate per day till Christmas, just solve a small programming problem each day :).

[Advent of Code 2017](http://adventofcode.com/2017 "adventofcode.com")

```
|O|        Naughty      |        Nice         |O|
|O|  -------------------+-------------------  |O|       
|O|  The Easter Bunny   | mcarmenjc           |O|
|O|  Kate Miháliková    | Galen Elias         |O|
|O|  Tim Vermeulen      | balefrost           |O|
|O|  HiggstonRainbird   | Ian Savchenko       |O|
|O|  Adé Mochtar        | Ben Buchwald        |O|
       
.-----------------------------------------------.       
| *──────────┬──────────────────|(──┐o───┬────┐ |  25 **
| ├─┐o───────┘┌─┤[]├───────────────*└────┘┌───┘ |  24 **
| └o└─────────┴─┬─o*───────────────┘o─────┴───o |  23 **
| ┌───────────┬┴┴┴┐└─┐┌─────────[─]──|(───────* |  22 **
| └──oTo─┬┴┴┴┬┤   ├──┘└┐o───────┐*────────────┘ |  21 **
| ┌──────┤ EB├┤   ├────┘┌─┤|├───┘└────────────* |  20 **
| └────┐┌┤ NL├┤  A├─────┴────┐*────[─]────────┘ |  19 **
| ┌────┘│┤ CT├┤  L├─────┬────┘└───|(──────────* |  18 **
| └───┐┌┘┤ AR├┤  U├V┌───┘*────────────┬──────┬┘ |  17 **
| ┌───┘│┌┴┬┬┬┴┴┬┬┬┘└┴───┐└───────────┐=┌──*o─┤V |  16 **
| ├────┘├o└─────────┐o──┴┬o*┬───────┐└─┴─o└─┐└┘ |  15 **
| └───┐┌┘┌┴┴┴┴┬─────┘┌─┐o┘┌┘=┌───*o─┴──────┐└─┐ |  14 **
| ┌───┘└o┤  30├──────┴o└─┐└──┴──o└────*┌──o└──┤ |  13 **
| └──────┤  29├──────o┌──┴┐*──────────┘└──────┘ |  12 **
| ┌──────┤  83├──────┬┘o─┬┘└────oTo───────────* |  11 **
| │o────┬┤  P6├──────┘*─┐└───┬─o┌───────┐┌────┘ |  10 **
| └───┬─┘┤    ├*──────┘V└─┐o─┘┌┐└────┐┌─┘└────┐ |   9 **
| ┌───┘*─┴┬┬┬┬┴┘o──┬──o├──┴───┘└─────┘└───────┤ |   8 **
| └─┐o┐└───────┐┌─┐└───┴o┌──┤[]├───────*o────┐│ |   7 **
| V┌┴─┴o┌──────┘└┐└──────┘*────────────┘┌──┬─┘│ |   6 **
| └┘┌───┤┌───────┴───────o└──────┬───*┌─┘o─┘┌─┘ |   5 **
| ┌─┘o──┘└────┐*───∧∧∧──────────┐└o┌─┘└─┬───┘o┐ |   4 **
| └───────────┘└─∧∧∧────────┬*o─┴─┐└───┐└─┤|├─┘ |   3 **
| *────────────────────────┐=└───┐└───┐└───|(─┐ |   2 **
| └─────────────────────*o─┴─────┘o───┴───∧∧∧─┘ |   1 **
'-----------------------------------------------'| 
```

## Compilation

To make things easier, I have created a makefile file to generate all the executables or just the one for a specific day. I think you need to create the bin folder under the project directory, as the makefile won't create this folder.

If you want to get all the executables just execute `make all`

To get the executable for just one day do `make day_X` with X in (1, 25)

## Test

To try get the solution of a day, you can do `bin/day_X` with X in (1, 25), and it will give you information about the parameters each day needs.

For example, 

```
bin/day_24 day_24/ports.txt
bin/day_25 12345
```