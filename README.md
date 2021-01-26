# COVID-19-Vaccinations-Management

## About The Project

Attempt to manage COVID-19 vaccinations using data structures. I have considered levels like countries and states. The solution supports the following features -
* Summarize the number of people vaccinated.
* Check if a person is vaccinated.
* Vaccinate a person.
* Every country has a different condition that has been considered for vaccination. Ex - In India, medical professionals have the highest priority. In the United States, senior citizens have the highest priority.

![COVID-19-Vaccinations-Management-Screenshot](https://github.com/harishpb26/COVID-19-Vaccinations-Management/blob/main/ds.png)

Each element of the country array points to the state array. Each element of the state array points to People that contains metadata such as the number of people, number of people vaccinated. People node then points to Persons of the state stored as a binary search tree.

## Installation
To clone and run this program, you'll need Git and C++ installed on your machine. From your command line:

1. Clone this repository
  ```sh
  $ git clone https://github.com/harishpb26/COVID-19-Vaccinations-Management
  ```
2. Go into the repository
  ```bash
  $ cd COVID-19-Vaccinations-Management
  ```
3. Conpile the program
  ```bash
  $ g++ covid.cpp
  ```
4. Run the executable
  ```bash
  $ ./a.out
```
