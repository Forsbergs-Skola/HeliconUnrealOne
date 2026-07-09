# Brad Neal

## The Unseen (Helicon Studios): Individual Contributions and Personal Reflections

### My Technical Contributions

#### Singleton Services
I designed and implemented our [singleton solution](./game_instance_as_singleton.md) as [UCPP_HeliconGameInstance].

- Header: [CPP_HeliconGameInstance.h](../Source/HeliconUnreal/Public/CPP_HeliconGameInstance.h)
- Implementation: [CPP_HeliconGameInstance.cpp](../Source/HeliconUnreal/Private/CPP_HeliconGameInstance.cpp)

#### Event System
I designed and implemented the centralized [event system](./event_service_and_tags.md) as UCPP_EventRelay.

- Header: [CPP_EventRelay.h](../Source/HeliconUnreal/Public/CPP_EventRelay.h)
- Implementation: [CPP_EventRelay.cpp](../Source/HeliconUnreal/Private/CPP_EventRelay.cpp)

#### Dialogue System
I designed our game's [branching dialogue system](./dialogue_system.md) as UCPP_DialogueService and WBP_DialogueUI.

#### Sliding-Tile Puzzle
I designed and implemented a widget-based sliding tile puzzle, and integrated it into the overall game sequence via the singleton services mentioned above.

### Personal Reflections

#### What the team did well
I'll be frank -- The biggest challenge with writing this evaluation is keeping this section brief. I genuinely loved working with every member of this team. We all brought different perspectives and approaches to game development, which strengthened both our collaborative process and the final result.

Our communication was naturally smooth and respectful at all times, which empowered us to work efficiently and support one another when needed. Everyone remained open to both giving and receiving feedback, which created a strong and supportive learning environment. I would gladly work with any or all of my Team Helicon colleagues again. 

#### Improvement opportunities for the team
As a group, this was our first project using Unreal Engine. This introduced a shared learning curve. Transitioning from a Unity background presented several challenges, particularly in understanding Unreal’s workflows, tools, and conventions.

While this created some initial friction, it also highlighted an important area for growth. As a team, we would benefit from developing a stronger foundation in Unreal Engine, allowing us to work more efficiently and avoid common pitfalls in future projects.

#### What I did well
I beleive that I was able to effectively apply some key concepts and patterns from this education in what, for all of us, is a new development context (UE/C++). This includes applying design patterns such as Singleton and Observer (publish–subscribe), as well as maintaining a focus on clean code principles.

I also worked to separate logic from data and structure systems using a layered architecture. These choices helped improve code organization, readability and maintainability within the project.

#### Improvement opportunities for me
One area for my personal improvement is balancing technical implementation with creative contributions. As a team of programmers, much of our focus naturally shifts toward development, but the project also required significant input in creative areas like game design and narrative design.

I found myself prioritizing programming tasks at the expense of these creative aspects, particularly toward the end of the project. During the final week, I was approaching a level of fatigue that made it difficult for me to engage creatively when it was most needed. For example, while I was able to design and implement a robust dialogue system, I struggled to contribute actual dialogue content.

In future projects, I'll try to manage my time and energy more mindfully. I'd like to be able to contribute both technically and creatively throughout the entire development process.