#ifndef TINYXMLSCMLLOADER_H
#define TINYXMLSCMLLOADER_H

#include "../../spriterengine/global/global.h"

#include "../../spriterengine/override/spriterfileloader.h"

#include "../../spriterengine/loading/loadinghelpers.h"

#include "../../spriterengine/loading/loader.h"

#include "../../tinyxml2/tinyxml2.h"

namespace SpriterEngine
{
	class SpriterModel;
	class Entity;
	class VariableContainer;
	class Animation;
	class Object;
	class TimeInfo;
	class EasingCurveInterface;
	class UniversalObjectInterface;
	class Timeline;
	class MainlineKey;
	class FileFlattener;

	class TinyXmlScmlLoader : public SpriterFileLoader
	{
	public:
		void loadFile(SpriterModel *model, const std::string &fileName) override;

	private:
		bool equal(const std::string & a, const std::string & b);
		const tinyxml2::XMLAttribute * findAttributeInElement(tinyxml2::XMLElement * element, const std::string & name, const tinyxml2::XMLAttribute *startingAtt = 0);

		void getFolderFileStructureFromElement(tinyxml2::XMLElement * spriterDataElement, SpriterModel * model, std::string scmlFileName, FileFlattener * fileFlattener);
		void getTagListFromElement(tinyxml2::XMLElement * spriterDataElement, SpriterModel * model);

		void getEntitiesFromElement(tinyxml2::XMLElement * spriterDataElement, SpriterModel * model, FileFlattener * fileFlattener);
		Entity * getNewEntityFromEntityElement(tinyxml2::XMLElement * entityElement, SpriterModel * model);
		void getObjectInfoFromEntityElement(tinyxml2::XMLElement * entityElement, Entity * entity, PointMap *defaultBoxPivotMap);

		void getVarDefArrayFromElement(tinyxml2::XMLElement * parentObjectElement, VariableContainer * parentObjectAsVariableContainer);

		void getCharacterMapsFromEntityElement(tinyxml2::XMLElement * entityElement, SpriterModel * model, Entity * entity, FileFlattener * fileFlattener);

		void getAnimationsFromEntityElement(tinyxml2::XMLElement * entityElement, SpriterModel * model, Entity * entity, FileFlattener * fileFlattener, PointMap *defaultBoxPivotMap);
		Animation * getNewAnimationFromAnimationElement(tinyxml2::XMLElement * animationElement, Entity * entity);

		void getTimelinesFromAnimationElement(tinyxml2::XMLElement * animationElement, SpriterModel * model, Entity * entity, Animation * animation, FileFlattener * fileFlattener, SpriteKeyFileInfoObjectIdMap * spriteKeyFileInfoMap, SubEntityKeyInfoMap * subEntityKeyInfoMap, PointMap *defaultBoxPivotMap);

		void createRedundantFirstKeys(Animation * animation, Timeline * timeline);

		void getMetaDataFromElement(tinyxml2::XMLElement *parentObjectElement, SpriterModel *model, Entity *entity, Animation *animation, int objectId);

		void getVarlinesFromMetaDataElement(tinyxml2::XMLElement *animationElement, Entity *entity, Animation *animation, int objectId);

		UniversalObjectInterface * getObjectInfoFromVariableKeyElement(tinyxml2::XMLElement *variableKeyElement, Variable *variable);

		void getTaglinesFromMetaDataElement(tinyxml2::XMLElement *metaDataElement, SpriterModel *model, Animation *animation, int objectId);

		UniversalObjectInterface * getObjectInfoFromTagKeyElement(tinyxml2::XMLElement *tagKeyElement, SpriterModel *model);

		Object * getObjectFromTimelineElement(tinyxml2::XMLElement * timelineElement, Entity * entity);

		TimeInfo * getTimeInfoFromElement(tinyxml2::XMLElement * validCurrentKeyElement, tinyxml2::XMLElement * nextKeyElement, tinyxml2::XMLElement * validFirstKeyElement, real animationLength, bool animationLooping);
		EasingCurveInterface * getEasingCurveFromAttributes(const tinyxml2::XMLAttribute * att);

		UniversalObjectInterface * getObjectInfoFromTimelineKeyElement(tinyxml2::XMLElement * keyElement, Entity * entity, Object * object, Timeline * timeline, FileFlattener * fileFlattener, SpriteKeyFileInfo * spriteKeyFileInfo, SubEntityKeyInfo *subEntityKeyInfo, point *defaultBoxPivot);

		void getMainlineFromAnimationElement(tinyxml2::XMLElement * animationElement, Animation * animation, SpriteKeyFileInfoObjectIdMap * spriteKeyFileInfoMap, SubEntityKeyInfoMap *subEntityKeyInfoMap);
		void getRefsFromMainlineKeyElement(tinyxml2::XMLElement * keyElement, Animation * animation, MainlineKey * mainlineKey, SpriteKeyFileInfoObjectIdMap * spriteKeyFileInfoMap, SubEntityKeyInfoMap *subEntityKeyInfoMap);

		void getEventlinesFromAnimationElement(tinyxml2::XMLElement * animationElement, Entity * entity, Animation * animation);

		void getSoundlinesFromAnimationElement(tinyxml2::XMLElement * animationElement, Entity * entity, Animation * animation, FileFlattener * fileFlattener);
		UniversalObjectInterface * getSoundObjectInfoFromSoundlineKey(tinyxml2::XMLElement * keyElement, Entity * entity, Object *object, FileFlattener * fileFlattener, bool * soundFileFound);
	};

}

#endif // TINYXMLSCMLOADER_H