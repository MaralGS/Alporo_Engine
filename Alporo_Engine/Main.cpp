#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"


#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

int main(int argc, char ** argv)
{
	LOG(LogType::WARNING,"Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG(LogType::LOGS,"-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG(LogType::LOGS, "-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG(LogType::ERRORS, "Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG(LogType::LOGS, "-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG(LogType::ERRORS, "Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG(LogType::LOGS, "-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG(LogType::ERRORS, "Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;
			
		}
	
	}

	delete App;
	LOG(LogType::LOGS, "Exiting game '%s'...\n", TITLE);
	ReportMemoryLeaks();
	return main_return;
}