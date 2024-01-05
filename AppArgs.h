#include <string_view>
#include <cstring>
#include <iostream>

namespace AppArgs {

	class Arg {
	public:
		friend class Args;

		/*
			Get the next argument

			@return Pointer to next argument, nullptr if unavailable
		*/
		Arg* Next() const { return m_NextArg; }

		/*
			@return Position of the argument
		*/
		int GetIndex() const { return m_Index; }

		operator const char*() const { return m_ArgString; }
		
		// Doubtful anyone would need the argument's memory address printed... override it
		friend std::ostream& operator<<(std::ostream& os, const Arg* arg);

	private:
		Arg() = default;
		~Arg() {}

	private:
		Arg* m_NextArg = nullptr;
		char* m_ArgString = nullptr;
		int m_Index = 0;
	};

	std::ostream& operator<<(std::ostream& os, const Arg* arg) {
		os << *arg;
		return os;
	}

	class Args {
	public:
		Args() = delete;

		/*
			Pass argument count and array from main function

			@param[in] argc Argument count
			@param[in] argv Argument array
		*/
		Args(int argc, char** argv) {
			m_Count = argc;
			m_Args = new Arg[argc];
			for (int i = 0; i < argc; i++) {
				m_Args[i].m_ArgString = argv[i];
				if (i < argc)
					m_Args[i].m_NextArg = &m_Args[i + 1];
			}
		}

		~Args() { delete[] m_Args; }

		/*
			Searches for the argument requested

			@param[in] arg The argument string to search for
			@return Pointer to the requested argument, nullptr if not found	
		*/
		Arg* Find(std::string_view arg) {
			for (int i = 0; i < m_Count; i++) {
				if (strncmp(m_Args[i], arg.data(), arg.size()) == 0)
					return &m_Args[i];
			}

			return nullptr;
		}

		/*
			@return Number of arguments
		*/
		int Size() const { return m_Count; }

		/*
			@return Argument by index
		*/
		Arg* operator[](int index) const { return &m_Args[index]; }

	private:
		int m_Count = 0;
		Arg* m_Args = nullptr;
	};

}