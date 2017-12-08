#ifndef __MOV_FILE_IO_HPP__
#define __MOV_FILE_IO_HPP__

#include <string>
#include <memory>

#if defined(_WIN32)
typedef std::wstring mov_string;
#else
typedef std::string mov_string;
#endif

struct Reader;

std::shared_ptr<Reader> createReader(const mov_string & path);


#endif //__MOV_FILE_IO_HPP__
