# Tongji University Data Structure Course Projects 2022

This repository contains the source code for the course design project on Data Structures. The project is based on the C++ programming language and focuses on implementing various data structures and algorithms.

## Project1: Exam Registration System
The examination registration work brings new challenges to the registration work of universities and adds a great workload to the academic affairs management. This project is a simple simulation of exam registration management, using the console option to complete the following functions: input candidate information; output candidate information; query candidate information; add candidate information; modify candidate information; delete candidate information.

## Project2: The intersection of two sequences of ordered linked tables
Knowing two sequences of non-descending chain tables S1 and S2, design a function to construct a new chain table S3 of the intersection of S1 and S2.

## Project3: Maze game
The process of solving the maze problem can be used backtracking method that is in a certain constraint to try to search forward, if the advance is blocked, it is timely to turn back to correct the error and choose another path to continue the search method. From the entrance, according to a certain direction to explore forward, if you can go through, that is, a certain place can be reached, then reach the new point, otherwise explore the next direction; if all the directions are no access, then return to the previous point along the original road, for the next direction and then continue to try until all possible roads are explored, or find a pathway, or no way to go back to the entrance point. In the solution process, in order to ensure that after reaching a point can not continue to walk forward, can correctly return to the previous in order to try forward from the next direction, it is necessary to save the subscript of each point that can be reached in the trial process and the direction of the point forward, when the exit is found when the trial process is over.

## Project4: Expression conversion
Arithmetic expressions have forms such as prefix representation, midfix representation and postfix representation. Arithmetic expressions in everyday use use use the midfix representation, where the binary operator is located in the middle of two operators. Please design a program to convert a midfix expression into a suffix expression.

## Project5: Banking
Let a bank have two business windows A and B, and the speed of processing business is not the same, where window A is twice as fast as window B ---- that is, when window A finishes processing every 2 customers, window B finishes processing 1 customer. Given the sequence of customers arriving at the bank, output the sequence of customers in the order of business completion. Assume that the time interval between the arrival of customers after the letter is not considered, and that when two customers are processed at the same time in different windows, the customers in window A are outputted first.

## Project6: Genealogy Management System
Genealogy is a special book genre that records the lineage reproduction and important tasks of a family mainly by blood relations in the form of a table of contents. Genealogy is a unique Chinese cultural heritage, one of the three major documents of the Chinese nation (national history, geography, and genealogy), and a precious human resource with unique and irreplaceable functions for in-depth research in history, folklore, demography, sociology, and economics. This project is a simple simulation of genealogy management, in order to realize the functions of viewing personal information of ancestors and descendants, inserting family members and deleting family members.

## Project7: Repair Ranch
The farmer wants to repair a section of fence on his ranch. He measures the fence and finds that he needs N pieces of wood, each of integer Li units of length, so he purchases a very long one that can be sawn into N pieces, i.e., the length of the piece of wood is the sum of Li.

But the farmer does not have a saw of his own, and the fee for hiring someone to saw the wood is proportional to the length of the piece of wood. For simplicity, let the fee be equal to the length of the log being sawed. For example, to saw a log of length 20 into three pieces of length 8, 7 and 5, the first sawing of the log into 12 and 8 will cost 20; the second sawing of the log into 7 and 5 will cost 12, for a total cost of 32 yuan. If the first sawed the wood into 15 and 5, then the second sawed the wood into 7 and 8, then the total cost is 35 (greater than 32).

## Project8: Power grid construction cost simulation system
Suppose there are n neighborhoods in a city, and it is necessary to construct the grid between the n neighborhoods in the city so that the total project cost is the lowest. Please design a cost solution that meets the requirements.

## Project9: Key Activities
This lab project requires that the minimum time required to complete the entire project be calculated if the time required to complete each word task is also given in the task scheduling problem. Some of these subtasks, called "critical activities", can be delayed by a few days without affecting the overall schedule, but some tasks must be completed on time or the entire project will be delayed.

## Project10: Comparative examples of 8 sorting algorithms

The random function generates one hundred, one thousand, ten thousand and one hundred thousand random numbers, which are sorted by the sorting methods of quick sort, direct insertion sort, bubble sort and selection sort, and counts the sorting time and the number of swaps spent in each sort. In which, the number of random numbers is defined by the user and the system generates the random numbers. And show the number of times they are compared.

Please document the computation time and storage overhead of each sort for the above amount of data, and explain the advantages and disadvantages of these methods based on the experimental results.

## Environment and Compilation

The project is developed using the Visual Studio 2019 IDE. To compile the code, simply open the corresponding Visual Studio solution (.sln) file in each folder and build the project.

## Note

Please note that this repository is for educational purposes only. Do not use the code in any commercial projects or for any other purposes without permission.
