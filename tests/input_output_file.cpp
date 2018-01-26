/*
 * input_output_file.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: martinelli
 */

#include <iostream>
#include <string>
#include <pico/pico.hpp>
#include <catch.hpp>
#include <io.hpp>

using namespace pico;


TEST_CASE( "read and write", "read and write tag" ){

	std::string input_file = "input_output_file.cpp"; //this file
	std::string output_file = "output.txt";

	/* define i/o operators from/to file */
	ReadFromFile reader(input_file);
	WriteToDisk<std::string> writer(output_file, [&]( std::string s) {
			return s;
	});

	/* compose the pipeline */
	auto io_file_pipe = Pipe() //the empty pipeline
	.add(reader)
	.add(writer);

	io_file_pipe.run();

	std::vector<std::string> input_lines = read_lines(input_file);
	std::vector<std::string> output_lines = read_lines(output_file);

	REQUIRE(input_lines == output_lines);
}

