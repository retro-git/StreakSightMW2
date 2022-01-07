#pragma once

namespace Utils
{
	/*
	* @brief Scan for a given byte pattern on a module
	*
	* @param module    Base of the module to search
	* @param signature IDA-style byte array pattern
	*
	* @returns Address of the first occurence
	*/
	std::uint8_t* PatternScan(void* module, const char* signature);
}