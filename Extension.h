
class Extension
{
public:

    LPRDATA rdPtr;
    LPRH    rhPtr;

    Edif::Runtime Runtime;

    static const int MinimumBuild = 251;
    static const int Version = 1;

    static const int OEFLAGS = OEFLAG_SPRITES|OEFLAG_MOVEMENTS|OEFLAG_VALUES|OEFLAG_BACKSAVE;
	static const int OEPREFS = OEPREFS_BACKSAVE | OEPREFS_BACKEFFECTS | OEPREFS_INKEFFECTS | OEPREFS_KILL;
    
    static const int WindowProcPriority = 100;

	static const int ERRORSIZE = 1000;

    Extension(LPRDATA rdPtr, LPEDATA edPtr, fpcob cobPtr);
    ~Extension();


    /*  Add any data you want to store in your extension to this class
        (eg. what you'd normally store in rdPtr)

        Unlike rdPtr, you can store real C++ objects with constructors
        and destructors, without having to call them manually or store
        a pointer.
    */

    string scmlFileString;
	SpriterEngine::EntityInstance *scmlObj;
	SpriterEngine::SpriterModel *scmlModel;
	unordered_map<string, Sprite> SpriteSource;
	unordered_map<string, UINT> SoundBank; // unordered_map<sound path in spriter file, sound id in CF25 sound bank>
	unordered_map<string, LPRO> BoxLink;
	unordered_map<string, UINT> SoundEvent;
	unordered_map<string, UINT> TriggerEvent;
	TCHAR lastError[ERRORSIZE];
	TCHAR errorTemp[ERRORSIZE];
	int deltaTime;
	int currentSystemTime;
	bool animPlaying;
	bool flipX;
	float speedRatio;
	RECT displayRect;

	string currentAnimationName; //TODO: replace by a direct access to spriter engine

	/*  Add your actions, conditions and expressions as real class member
        functions here. The arguments (and return type for expressions) must
        match EXACTLY what you defined in the JSON.

        Remember to link the actions, conditions and expressions to their
        numeric IDs in the class constructor (Extension.cpp)
    */
	bool IsScmlObjectValid();
	string getFirstAnimationName();

    /// Actions
	void StopAnimation();
	void StartAnimation();
	void ChangeAnimationByName(TCHAR* name);
	void ChangeAnimationByNameWithBlending(TCHAR* name, int blendingTime);
	void ChangeAnimationTime(int timeMs);
	void ChangeEntityByNumber(int num);
	void SetFlipX(int enable);
	void SetAnimationSpeed(float speed);
	void ApplyCharacterMap(TCHAR* name);
	void RemoveCharacterMap(TCHAR* name);
	void RemoveAllCharacterMaps();
	void SetScale(float scale);
	void SetAngle(float angle);
	void LoadSpriteFromActive(string spriteName, LPRO pObj, int nAmim, int nDir, int nFrame);
	void LoadOneSpriteFromActive(TCHAR* spriteName, LPRO pObj, int nAmim, int nDir, int nFrame);
	void LoadOrderedSpritesPerAnimation(LPRO pObj, int nAnim);
	void LoadOrderedSpritesPerDirection(LPRO pObj, int nAnim, int nDir);
	void LoadSoundFromSoundBank(TCHAR* soundPath, TCHAR* soundName);
	void BoundBoxToObject(TCHAR* boxName, LPRO object);
	void UnboundBoxFromObject(TCHAR* boxName);
	void SetDebug(int showBones, int showBoxes, int showPoints);
	void LoadScmlFile(TCHAR* filename);

    /// Conditions
	bool IsAnimationPlayingByName(TCHAR* name);
	bool HasCurrentAnimationFinished();
	long CompareCurrentTimeToValue(int val);
	bool IsTagActive(TCHAR* tagName);
	bool IsObjectTagActive(TCHAR* objectName, TCHAR* tagName);
	bool OnSoundEvent(TCHAR* soundName);
	bool OnTriggerEvent(TCHAR* triggerName);
	bool IsAnimationFlipped();
    /// Expressions
	TCHAR * LastError();
	TCHAR * CurrentAnimationName();
	float GetScale();
	float GetAngle();
	int CurrentTime();
	float CurrentSpeedRatio();
	float GetRealVariable(TCHAR* variableName);
	float GetObjectRealVariable(TCHAR* objectName, TCHAR* variableName);
	int GetIntVariable(TCHAR* variableName);
	int GetObjectIntVariable(TCHAR* objectName, TCHAR* variableName);
	TCHAR* GetStringVariable(TCHAR* variableName);
	TCHAR* GetObjectStringVariable(TCHAR* objectName, TCHAR* variableName);
	int GetPointPosX(TCHAR* pointName);
	int GetPointPosY(TCHAR* pointName);
	float GetPointAngle(TCHAR* pointName);

    /* These are called if there's no function linked to an ID */

    void Action(int ID, LPRDATA rdPtr, long param1, long param2);
    long Condition(int ID, LPRDATA rdPtr, long param1, long param2);
    long Expression(int ID, LPRDATA rdPtr, long param);
	
    /*  These replace the functions like HandleRunObject that used to be
        implemented in Runtime.cpp. They work exactly the same, but they're
        inside the extension class.
    */

    short Handle();
    short Display();

    short Pause();
    short Continue();

    bool Save(HANDLE File);
    bool Load(HANDLE File);

};