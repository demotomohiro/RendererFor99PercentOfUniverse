#pragma warning( push, 1 )

#include <iostream>
#include <boost/program_options.hpp>

#pragma warning( pop )

#include "options.hpp"

using namespace boost;
using namespace std;

options::options(int argc, char* argv[]):
	is_render(false),	ret_code(0),
	source_file("main_shader.frag")
{
	//�����ł�OpenGL�̊֐����Ăяo���Ă͂����Ȃ�.
	try
	{
	program_options::options_description desc("Allowed options");
	desc.add_options()
		("help",	"produce help message")
		("source",		program_options::value<string>(),	"Fragment shader source")
		("output_w",	program_options::value<GLsizei>(),	"Output image width")
		("output_h",	program_options::value<GLsizei>(),	"Output image height")
		("num_tile_x",	program_options::value<GLsizei>(),	"Number of tiles in x axis")
		("num_tile_y",	program_options::value<GLsizei>(),	"Number of tiles in y axis")
		("super_sampling_level",	program_options::value<GLsizei>(), "super sampling level")
	;

	program_options::positional_options_description	p;
	p.add("source", 1);

	program_options::variables_map vm;
	program_options::store
	(
		program_options::command_line_parser
		(
			argc, argv
		).options(desc).positional(p).run(),
		vm
	);
	program_options::notify(vm);	

	if(vm.count("help"))
	{
		cout << desc << "\n";
		return;
	}

	if(vm.count("output_w"))
	{
		rinfo.output_w = vm["output_w"].as<GLsizei>();
		cout << "output_w: " << rinfo.output_w << '\n';
	}
	/*
	else {
		cout << "output_w was not set.\n";
	}
	*/
	if(vm.count("output_h"))
	{
		rinfo.output_h = vm["output_h"].as<GLsizei>();
		cout << "output_h: " << rinfo.output_h << '\n';
	}

	if(vm.count("num_tile_x"))
	{
		rinfo.num_tile_x = vm["num_tile_x"].as<GLsizei>();
		cout << "num_tile_x: " << rinfo.num_tile_x << '\n';
	}

	if(vm.count("num_tile_y"))
	{
		rinfo.num_tile_y = vm["num_tile_y"].as<GLsizei>();
		cout << "num_tile_y: " << rinfo.num_tile_y << '\n';
	}

	if(vm.count("super_sampling_level"))
	{
		rinfo.super_sampling_level = vm["super_sampling_level"].as<GLsizei>();
		cout << "super_sampling_level: " << rinfo.super_sampling_level << '\n';
	}

	if(rinfo.output_w % rinfo.num_tile_x != 0)
	{
		cerr << "output_w % num_tile_x must be 0!\n";
		return;
	}

	if(rinfo.output_h % rinfo.num_tile_y != 0)
	{
		cerr << "output_h % num_tile_y must be 0!\n";
		return;
	}

	if(rinfo.super_sampling_level > 31)
	{
		cerr << "super_sampling_level must be smaller than 32!\n";
		return;
	}

	if(vm.count("source"))
	{
		source_file = vm["source"].as<string>();
		is_render = true;
	}

	}catch(std::exception& e)
	{
		cout << e.what() << "\n";
		return;
	}

	is_render = true;
	ret_code = 0;
}
