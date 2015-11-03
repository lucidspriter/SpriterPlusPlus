#include "tinyxmlscmlloader.h"

#include "../../tinyxml2/tinyxml2.h"

#include "../../spriterengine/model/spritermodel.h"
#include "../../spriterengine/global/global.h"

#include "../../spriterengine/timeinfo/instanteasingcurve.h"
#include "../../spriterengine/timeinfo/lineareasingcurve.h"
#include "../../spriterengine/timeinfo/timeinfo.h"

#include "../../spriterengine/objectinfo/boneobjectinfo.h"
#include "../../spriterengine/objectinfo/boxobjectinfo.h"
#include "../../spriterengine/objectinfo/entityobjectinfo.h"
#include "../../spriterengine/objectinfo/triggerobjectinfo.h"
#include "../../spriterengine/objectinfo/tagobjectinfo.h"

#include "../../spriterengine/objectref/boneref.h"
#include "../../spriterengine/objectref/objectref.h"
#include "../../spriterengine/objectref/spriteref.h"
#include "../../spriterengine/objectref/entityref.h"


namespace SpriterEngine
{
	void TinyXmlScmlLoader::loadFile(SpriterModel *model, const std::string &fileName)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(fileName.c_str());

		tinyxml2::XMLElement *spriterDataElement = doc.FirstChildElement("spriter_data");
		if (spriterDataElement)
		{
			FileFlattener fileFlattener;
			getFolderFileStructureFromElement(spriterDataElement, model, fileName, &fileFlattener);
			getTagListFromElement(spriterDataElement, model);
			getEntitiesFromElement(spriterDataElement, model, &fileFlattener);
		}
		else
		{
			// error
			return;
		}
	}

	bool TinyXmlScmlLoader::equal(const std::string &a, const std::string &b)
	{
		return a == b;
	}

	const tinyxml2::XMLAttribute *TinyXmlScmlLoader::findAttributeInElement(tinyxml2::XMLElement *element, const std::string &name, const tinyxml2::XMLAttribute *startingAtt)
	{
		const tinyxml2::XMLAttribute *att = startingAtt;
		if (!att)
		{
			att = element->FirstAttribute();
		}

		while (att)
		{
			if (equal(att->Name(), name))
			{
				return att;
			}
			att = att->Next();
		}

		return 0;
	}

	void TinyXmlScmlLoader::getFolderFileStructureFromElement(tinyxml2::XMLElement *spriterDataElement, SpriterModel *model, std::string scmlFileName, FileFlattener *fileFlattener)
	{
		std::string filePath = extractFilePath(scmlFileName);
		tinyxml2::XMLElement *folderElement = spriterDataElement->FirstChildElement("folder");
		while (folderElement&&equal(folderElement->Value(), "folder"))
		{
			fileFlattener->appendFolder();
			tinyxml2::XMLElement *fileElement = folderElement->FirstChildElement();
			while (fileElement&&equal(fileElement->Value(), "file"))
			{
				fileFlattener->appendFile();

				const tinyxml2::XMLAttribute *att = findAttributeInElement(fileElement, "name");
				std::string fileName;
				if (att)
				{
					fileName = att->Value();
					att = att->Next();
				}
				else
				{
					// error
					return;
				}

				if (att&&equal(att->Name(), "type"))
				{
					if (equal(att->Value(), "sound"))
					{
						model->pushBackSoundFile(filePath + fileName);
					}
				}
				else
				{
					point pivot(0, 1);
					if (att&&equal(att->Name(), "width"))
					{
						// TODO: if you need the width of the file for your implementation retrieve it here;
						att = att->Next();
					}
					if (att&&equal(att->Name(), "height"))
					{
						// TODO: if you need the height of the file for your implementation retrieve it here;
						att = att->Next();
					}
					if (att&&equal(att->Name(), "pivot_x"))
					{
						pivot.x = att->DoubleValue();
						att = att->Next();
					}
					if (att&&equal(att->Name(), "pivot_y"))
					{
						pivot.y = 1 - att->DoubleValue();
						att = att->Next();
					}
					model->pushBackImageFile(filePath + fileName, pivot);
				}

				fileElement = fileElement->NextSiblingElement();
			}

			folderElement = folderElement->NextSiblingElement();
		}
	}

	void TinyXmlScmlLoader::getTagListFromElement(tinyxml2::XMLElement *spriterDataElement, SpriterModel *model)
	{
		tinyxml2::XMLElement *tagListElement = spriterDataElement->FirstChildElement("tag_list");
		if (tagListElement&&equal(tagListElement->Value(), "tag_list"))
		{
			tinyxml2::XMLElement *tagElement = tagListElement->FirstChildElement();
			while (tagElement)
			{
				const tinyxml2::XMLAttribute *att = findAttributeInElement(tagElement, "name");
				if (att)
				{
					model->pushBackTag(att->Value());
				}
				else
				{
					// error
					return;
				}

				tagElement = tagElement->NextSiblingElement();
			}

			tagListElement = tagListElement->NextSiblingElement();
		}
	}

	void TinyXmlScmlLoader::getEntitiesFromElement(tinyxml2::XMLElement *spriterDataElement, SpriterModel *model, FileFlattener *fileFlattener)
	{
		tinyxml2::XMLElement *entityElement = spriterDataElement->FirstChildElement("entity");
		while (entityElement&&equal(entityElement->Value(), "entity"))
		{
			Entity *entity = getNewEntityFromEntityElement(entityElement, model);
			if (entity)
			{
				PointMap defaultBoxPivotMap;
				getObjectInfoFromEntityElement(entityElement, entity, &defaultBoxPivotMap);
				getVarDefArrayFromElement(entityElement, entity);
				getCharacterMapsFromEntityElement(entityElement, model, entity, fileFlattener);
				getAnimationsFromEntityElement(entityElement, model, entity, fileFlattener, &defaultBoxPivotMap);
				entity->setupDefaultVariableTimelines();
			}
			else
			{
				// error
				return;
			}

			entityElement = entityElement->NextSiblingElement();
		}

	}

	Entity *TinyXmlScmlLoader::getNewEntityFromEntityElement(tinyxml2::XMLElement *entityElement, SpriterModel *model)
	{
		const tinyxml2::XMLAttribute *nameAtt = findAttributeInElement(entityElement, "name");
		Entity *entity = 0;
		if (nameAtt)
		{
			return model->pushBackEntity(nameAtt->Value());
		}
		else
		{
			// error
			return 0;
		}
	}

	void TinyXmlScmlLoader::getObjectInfoFromEntityElement(tinyxml2::XMLElement *entityElement, Entity *entity, PointMap *defaultBoxPivotMap)
	{
		tinyxml2::XMLElement *objInfoElement = entityElement->FirstChildElement("obj_info");
		while (objInfoElement&&equal(objInfoElement->Value(), "obj_info"))
		{
			const tinyxml2::XMLAttribute *att = findAttributeInElement(objInfoElement, "name");
			if (att)
			{
				std::string objectName = att->Value();
				att = att->Next();

				Object::ObjectType objectType = Object::OBJECTTYPE_SPRITE;
				if (att && equal(att->Name(), "type"))
				{
					objectType = objectTypeNameToType(att->Value());
					att = att->Next();
				}

				Object *newObject = entity->setObject(objectName, objectType);

				if (newObject)
				{
					if (objectType == Object::OBJECTTYPE_BONE || objectType == Object::OBJECTTYPE_BOX)
					{
						point size;
						if (att && equal(att->Name(), "w"))
						{
							size.x = att->DoubleValue();
							att = att->Next();
						}
						if (att && equal(att->Name(), "h"))
						{
							size.y = att->DoubleValue();
							att = att->Next();
						}
						if (att && equal(att->Name(), "pivot_x"))
						{
							(*defaultBoxPivotMap)[newObject->getId()].x = att->DoubleValue();
							att = att->Next();
						}
						if (att && equal(att->Name(), "pivot_y"))
						{
							(*defaultBoxPivotMap)[newObject->getId()].y = 1 - att->DoubleValue();
							att = att->Next();
						}
						newObject->setSize(size);
					}

					getVarDefArrayFromElement(objInfoElement, newObject);
				}
				else
				{
					// error
				}
			}
			else
			{
				// error
				return;
			}

			objInfoElement = objInfoElement->NextSiblingElement();
		}
	}

	void TinyXmlScmlLoader::getVarDefArrayFromElement(tinyxml2::XMLElement *parentObjectElement, VariableContainer *parentObjectAsVariableContainer)
	{
		tinyxml2::XMLElement *varDefArrayElement = parentObjectElement->FirstChildElement("var_defs");
		if (varDefArrayElement)
		{
			tinyxml2::XMLElement *varDefElement = varDefArrayElement->FirstChildElement("i");
			while (varDefElement)
			{
				const tinyxml2::XMLAttribute *att = findAttributeInElement(varDefElement, "name");
				if (att)
				{
					std::string varName = att->Value();
					att = att->Next();

					std::string varType = "";
					if (att && equal(att->Name(), "type"))
					{
						varType = att->Value();
						att = att->Next();
					}
					else
					{
						// error
						return;
					}

					if (att && equal(att->Name(), "default"))
					{
						if (varType == "float")
						{
							parentObjectAsVariableContainer->addRealVariable(varName, att->DoubleValue());
						}
						else if (varType == "string")
						{
							parentObjectAsVariableContainer->addStringVariable(varName, att->Value());
						}
						else
						{
							parentObjectAsVariableContainer->addIntVariable(varName, att->IntValue());
						}
					}
					else
					{
						// error
						return;
					}
				}
				else
				{
					// error
					return;
				}

				varDefElement = varDefElement->NextSiblingElement();
			}
		}
	}

	void TinyXmlScmlLoader::getCharacterMapsFromEntityElement(tinyxml2::XMLElement *entityElement, SpriterModel *model, Entity *entity, FileFlattener *fileFlattener)
	{
		tinyxml2::XMLElement *characterMapElement = entityElement->FirstChildElement("character_map");

		while (characterMapElement&&equal(characterMapElement->Value(), "character_map"))
		{
			const tinyxml2::XMLAttribute *nameAtt = findAttributeInElement(characterMapElement, "name");
			CharacterMap *newCharacterMap = 0;
			if (nameAtt)
			{
				newCharacterMap = entity->addCharacterMap(nameAtt->Value());
			}
			else
			{
				// error
				return;
			}

			tinyxml2::XMLElement *mapElement = characterMapElement->FirstChildElement();
			while (mapElement)
			{
				const tinyxml2::XMLAttribute *att = mapElement->FirstAttribute();
				if (att)
				{
					int sourceFolderIndex = NO_FILE;
					if (att && equal(att->Name(), "folder"))
					{
						sourceFolderIndex = att->IntValue();
						att = att->Next();
					}
					else
					{
						// error
						return;
					}

					int sourceFileIndex = NO_FILE;
					if (att && equal(att->Name(), "file"))
					{
						sourceFileIndex = att->IntValue();
						att = att->Next();
					}
					else
					{
						// error
						return;
					}

					int targetFolderIndex = NO_FILE;
					int targetFileIndex = NO_FILE;
					if (att && equal(att->Name(), "target_folder"))
					{
						targetFolderIndex = att->IntValue();
						att = att->Next();
						if (att && equal(att->Name(), "target_file"))
						{
							targetFileIndex = att->IntValue();
						}
					}

					newCharacterMap->appendMapInstruction(fileFlattener->getFlattenedIndex(sourceFolderIndex, sourceFileIndex), model->getFileAtIndex(fileFlattener->getFlattenedIndex(targetFolderIndex, targetFileIndex)));
				}
				else
				{
					// error
					return;
				}

				mapElement = mapElement->NextSiblingElement();
			}

			characterMapElement = characterMapElement->NextSiblingElement();
		}
	}

	void TinyXmlScmlLoader::getAnimationsFromEntityElement(tinyxml2::XMLElement *entityElement, SpriterModel *model, Entity *entity, FileFlattener *fileFlattener, PointMap *defaultBoxPivotMap)
	{
		tinyxml2::XMLElement *animationElement = entityElement->FirstChildElement("animation");
		while (animationElement&&equal(animationElement->Value(), "animation"))
		{
			Animation *newAnimation = getNewAnimationFromAnimationElement(animationElement, entity);
			if (newAnimation)
			{
				SpriteKeyFileInfoObjectIdMap spriteKeyFileInfoMap;
				SubEntityKeyInfoMap subEntityKeyInfoMap;
				getTimelinesFromAnimationElement(animationElement, model, entity, newAnimation, fileFlattener, &spriteKeyFileInfoMap, &subEntityKeyInfoMap, defaultBoxPivotMap);
				getMainlineFromAnimationElement(animationElement, newAnimation, &spriteKeyFileInfoMap, &subEntityKeyInfoMap);
				getEventlinesFromAnimationElement(animationElement, entity, newAnimation);
				getSoundlinesFromAnimationElement(animationElement, entity, newAnimation, fileFlattener);
				getMetaDataFromElement(animationElement, model, entity, newAnimation, THIS_ENTITY);
			}
			else
			{
				// error
				return;
			}

			animationElement = animationElement->NextSiblingElement();
		}
	}

	Animation *TinyXmlScmlLoader::getNewAnimationFromAnimationElement(tinyxml2::XMLElement *animationElement, Entity *entity)
	{
		Animation *newAnimation = 0;
		real animationLength = 0;
		bool animationLooping = true;
		const tinyxml2::XMLAttribute *att = findAttributeInElement(animationElement, "name");
		if (att)
		{
			std::string animationName = "";
			if (equal(att->Name(), "name"))
			{
				animationName = att->Value();
				att = att->Next();
			}
			else
			{
				// error
				return 0;
			}

			if (att && equal(att->Name(), "length"))
			{
				animationLength = att->DoubleValue();
				att = att->Next();
			}
			else
			{
				// error
				return 0;
			}

			att = findAttributeInElement(animationElement, "looping", att);
			if (att)
			{
				animationLooping = !equal(att->Value(), "false");
			}

			return entity->pushBackAnimation(animationName, animationLength, animationLooping);
		}
		else
		{
			// error
			return 0;
		}
	}

	void TinyXmlScmlLoader::getTimelinesFromAnimationElement(tinyxml2::XMLElement *animationElement, SpriterModel *model, Entity *entity, Animation *animation, FileFlattener *fileFlattener, SpriteKeyFileInfoObjectIdMap *spriteKeyFileInfoMap, SubEntityKeyInfoMap *subEntityKeyInfoMap, PointMap *defaultBoxPivotMap)
	{
		tinyxml2::XMLElement *timelineElement = animationElement->FirstChildElement("timeline");
		int timelineIndex = 0;
		while (timelineElement && equal(timelineElement->Value(), "timeline"))
		{
			Object *object = getObjectFromTimelineElement(timelineElement, entity);
			if (!object)
			{
				// error
				return;
			}

			Timeline *newTimeline = animation->pushBackObjectTimeline(object->getId());

			tinyxml2::XMLElement *firstKeyElement = timelineElement->FirstChildElement("key");
			tinyxml2::XMLElement *keyElement = firstKeyElement;

			SpriteKeyFileInfoVector *tempSpriteKeyFileInfoTimeline = 0;
			SubEntityKeyInfoVector *tempSubEntityKeyInfoTimeline = 0;

			point *defaultBoxPivot = 0;

			if (object->getType() == Object::OBJECTTYPE_SPRITE)
			{
				tempSpriteKeyFileInfoTimeline = &(*spriteKeyFileInfoMap)[object->getId()];
			}
			else if (object->getType() == Object::OBJECTTYPE_ENTITY)
			{
				tempSubEntityKeyInfoTimeline = &(*subEntityKeyInfoMap)[object->getId()];
			}
			else if (object->getType() == Object::OBJECTTYPE_BOX)
			{
				auto & it = defaultBoxPivotMap->find(object->getId());
				if (it != defaultBoxPivotMap->end())
				{
					defaultBoxPivot = &(*it).second;
				}
			}

			TimelineKey *firstKey = 0;
			TimelineKey *previousKey = 0;
			while (keyElement)
			{
				SpriteKeyFileInfo *tempSpriteKeyFileInfo = 0;
				SubEntityKeyInfo *tempSubEntityKeyInfo = 0;
				if (tempSpriteKeyFileInfoTimeline)
				{
					tempSpriteKeyFileInfoTimeline->push_back(SpriteKeyFileInfo());
					tempSpriteKeyFileInfo = &tempSpriteKeyFileInfoTimeline->back();
				}
				else if (tempSubEntityKeyInfoTimeline)
				{
					tempSubEntityKeyInfoTimeline->push_back(SubEntityKeyInfo());
					tempSubEntityKeyInfo = &tempSubEntityKeyInfoTimeline->back();
				}

				tinyxml2::XMLElement *nextKeyElement = keyElement->NextSiblingElement("key");
				TimeInfo *timeInfo = getTimeInfoFromElement(keyElement, nextKeyElement, firstKeyElement, animation->getLength(), animation->getIsLooping());
				UniversalObjectInterface *objectInfo = getObjectInfoFromTimelineKeyElement(keyElement, entity, object, newTimeline, fileFlattener, tempSpriteKeyFileInfo, tempSubEntityKeyInfo, defaultBoxPivot);

				if (!objectInfo)
				{
					// error
					return;
				}

				if (timeInfo)
				{
					if (previousKey)
					{
						previousKey->setNextObjectInfo(objectInfo);
					}
					previousKey = newTimeline->pushBackKey(timeInfo, objectInfo);
					if (!firstKey)
					{
						firstKey = previousKey;
					}
				}
				else
				{
					// error
					return;
				}

				keyElement = nextKeyElement;
			}

			if (previousKey)
			{
				if (animation->getIsLooping())
				{
					previousKey->setNextObjectInfo(firstKey->getObjectInfo());
				}
				else
				{
					previousKey->setNextObjectInfo(previousKey->getObjectInfo());
				}
			}

			createRedundantFirstKeys(animation, newTimeline);

			getMetaDataFromElement(timelineElement, model, entity, animation, object->getId());

			timelineElement = timelineElement->NextSiblingElement();
			++timelineIndex;
		}
	}
	
	void TinyXmlScmlLoader::createRedundantFirstKeys(Animation *animation, Timeline *timeline)
	{
		TimelineKey *firstKey = timeline->getKey(0);
		if (firstKey && firstKey->getTime() > 0)
		{
			TimelineKey *lastKey = timeline->getLastKey();
			timeline->pushFrontProxyKey(lastKey->getTime() - animation->getLength(), firstKey->getTime(), animation->getIsLooping());
		}
	}

	void TinyXmlScmlLoader::getMetaDataFromElement(tinyxml2::XMLElement *parentObjectElement, SpriterModel *model, Entity *entity, Animation *animation, int objectId)
	{
		tinyxml2::XMLElement *metaDataElement = parentObjectElement->FirstChildElement("meta");
		if (metaDataElement)
		{
			getVarlinesFromMetaDataElement(metaDataElement, entity, animation, objectId);
			getTaglinesFromMetaDataElement(metaDataElement, model, animation, objectId);
		}
	}

	void TinyXmlScmlLoader::getVarlinesFromMetaDataElement(tinyxml2::XMLElement *animationElement, Entity *entity, Animation *animation, int objectId)
	{
		tinyxml2::XMLElement *varlineElement = animationElement->FirstChildElement("varline");
		while (varlineElement && equal(varlineElement->Value(), "varline"))
		{
			const tinyxml2::XMLAttribute *att = findAttributeInElement(varlineElement, "def");
			if (!att)
			{
				// error
				return;
			}

			int variableId = att->IntValue();
			Timeline *newTimeline = animation->setVariableTimeline(objectId, variableId);
			Variable *variable = entity->getVariable(objectId, variableId);
			if (!variable)
			{
				// error
				return;
			}

			tinyxml2::XMLElement *firstKeyElement = varlineElement->FirstChildElement("key");
			tinyxml2::XMLElement *keyElement = firstKeyElement;

			TimelineKey *firstKey = 0;
			TimelineKey *previousKey = 0;
			while (keyElement)
			{
				tinyxml2::XMLElement *nextKeyElement = keyElement->NextSiblingElement();
				TimeInfo *timeInfo = getTimeInfoFromElement(keyElement, nextKeyElement, firstKeyElement, animation->getLength(), animation->getIsLooping());

				UniversalObjectInterface *objectInfo = getObjectInfoFromVariableKeyElement(keyElement, variable);
				if (!objectInfo)
				{
					// error
					return;
				}

				if (timeInfo)
				{
					if (previousKey)
					{
						previousKey->setNextObjectInfo(objectInfo);
					}
					previousKey = newTimeline->pushBackKey(timeInfo, objectInfo);
					if (!firstKey)
					{
						firstKey = previousKey;
					}
				}
				else
				{
					// error
					return;
				}

				keyElement = nextKeyElement;
			}

			if (previousKey)
			{
				if (animation->getIsLooping())
				{
					previousKey->setNextObjectInfo(firstKey->getObjectInfo());
				}
				else
				{
					previousKey->setNextObjectInfo(previousKey->getObjectInfo());
				}
			}

			createRedundantFirstKeys(animation, newTimeline);
			varlineElement = varlineElement->NextSiblingElement();
		}
	}

	UniversalObjectInterface *TinyXmlScmlLoader::getObjectInfoFromVariableKeyElement(tinyxml2::XMLElement *variableKeyElement, Variable *variable)
	{
		const tinyxml2::XMLAttribute *valAtt = findAttributeInElement(variableKeyElement, "val");
		if (!valAtt)
		{
			// error
			return 0;
		}

		UniversalObjectInterface *objectInfo = variable->getNewObjectInfoInstance();
		if (!objectInfo)
		{
			// error
			return 0;
		}

		switch (variable->getType())
		{
		case Variable::VARIABLETYPE_INT:
			objectInfo->setIntValue(valAtt->IntValue());
			break;

		case Variable::VARIABLETYPE_REAL:
			objectInfo->setRealValue(valAtt->DoubleValue());
			break;

		case Variable::VARIABLETYPE_STRING:
			objectInfo->setStringValue(valAtt->Value());
			break;

		default:
			// error;
			break;
		}

		return objectInfo;
	}

	void TinyXmlScmlLoader::getTaglinesFromMetaDataElement(tinyxml2::XMLElement *metaDataElement, SpriterModel *model, Animation *animation, int objectId)
	{
		tinyxml2::XMLElement *taglineElement = metaDataElement->FirstChildElement("tagline");
		while (taglineElement && equal(taglineElement->Value(), "tagline"))
		{
			Timeline *newTimeline = animation->pushBackTagTimeline(objectId);

			tinyxml2::XMLElement *firstKeyElement = taglineElement->FirstChildElement("key");
			tinyxml2::XMLElement *keyElement = firstKeyElement;
			while (keyElement)
			{
				tinyxml2::XMLElement *nextKeyElement = keyElement->NextSiblingElement();
				TimeInfo *timeInfo = getTimeInfoFromElement(keyElement, nextKeyElement, firstKeyElement, animation->getLength(), animation->getIsLooping());
				if (!timeInfo)
				{
					// error
					return;
				}

				UniversalObjectInterface *objectInfo = getObjectInfoFromTagKeyElement(keyElement, model);
				if (!objectInfo)
				{
					// error
					return;
				}
				
				TimelineKey * newKey = newTimeline->pushBackKey(timeInfo, objectInfo);
				newKey->setNextObjectInfo(newKey->getObjectInfo());

				keyElement = keyElement->NextSiblingElement();
			}

			createRedundantFirstKeys(animation, newTimeline);
			taglineElement = taglineElement->NextSiblingElement();
		}
	}

	UniversalObjectInterface * TinyXmlScmlLoader::getObjectInfoFromTagKeyElement(tinyxml2::XMLElement * tagKeyElement, SpriterModel *model)
	{
		TagObjectInfo *tagInfo = new TagObjectInfo();
		tinyxml2::XMLElement *tagElement = tagKeyElement->FirstChildElement();
		while (tagElement)
		{
			const tinyxml2::XMLAttribute *tagIdAtt = findAttributeInElement(tagElement, "t");
			if (!tagIdAtt)
			{
				// error
				return tagInfo;
			}

			const std::string *tag = model->getTag(tagIdAtt->IntValue());
			if (!tag)
			{
				// error
				return tagInfo;
			}

			tagInfo->pushBackTag(tag);
			tagElement = tagElement->NextSiblingElement();
		}

		return tagInfo;
	}

	Object *TinyXmlScmlLoader::getObjectFromTimelineElement(tinyxml2::XMLElement *timelineElement, Entity *entity)
	{
		std::string timelineName;
		Object::ObjectType timelineType = Object::OBJECTTYPE_SPRITE;
		const tinyxml2::XMLAttribute *att = findAttributeInElement(timelineElement, "name");
		Object *object = 0;
		if (att)
		{
			timelineName = att->Value();
			att = att->Next();
			if (att&&equal(att->Name(), "object_type"))
			{
				timelineType = objectTypeNameToType(att->Value());
			}

			return entity->setObject(timelineName, timelineType);
		}
		else
		{
			return 0;
		}
	}

	TimeInfo *TinyXmlScmlLoader::getTimeInfoFromElement(tinyxml2::XMLElement *validCurrentKeyElement, tinyxml2::XMLElement *nextKeyElement, tinyxml2::XMLElement *validFirstKeyElement, real animationLength, bool animationLooping)
	{
		real time = 0;
		real nextTime = 0;
		EasingCurveInterface *easingCurve = 0;
		if (nextKeyElement)
		{
			const tinyxml2::XMLAttribute *nextTimeAtt = findAttributeInElement(nextKeyElement, "time");
			if (nextTimeAtt)
			{
				nextTime = nextTimeAtt->DoubleValue();
			}
		}
		else if (animationLooping)
		{
			if (validFirstKeyElement == validCurrentKeyElement)
			{
				easingCurve = new InstantEasingCurve();
			}
			else
			{
				const tinyxml2::XMLAttribute *nextTimeAtt = findAttributeInElement(validFirstKeyElement, "time");
				if (nextTimeAtt)
				{
					nextTime = nextTimeAtt->DoubleValue();
				}
				nextTime += animationLength;
			}
		}
		else
		{
			easingCurve = new InstantEasingCurve();
		}

		const tinyxml2::XMLAttribute *att = validCurrentKeyElement->FirstAttribute();
		while (att)
		{
			if (equal(att->Name(), "time"))
			{
				time = att->DoubleValue();
			}
			else if (!easingCurve && equal(att->Name(), "curve_type"))
			{
				easingCurve = getEasingCurveFromAttributes(att);
			}
			att = att->Next();
		}

		if (!easingCurve)
		{
			easingCurve = new LinearEasingCurve();
		}

		return new TimeInfo(time, nextTime, easingCurve);
	}

	EasingCurveInterface *TinyXmlScmlLoader::getEasingCurveFromAttributes(const tinyxml2::XMLAttribute *att)
	{
		CurveType curveType = CURVETYPE_NONE;
		ControlPointArray controlPoints = { 0 };
		curveType = curveTypeNameToType(att->Value());
		if (curveType > CURVETYPE_LINEAR)
		{
			att = att->Next();
			int i = 0;
			while (att && i < MAX_CONTROL_POINTS)
			{
				controlPoints[i] = att->IntValue();
				++i;
				att = att->Next();
			}
		}

		return getNewEasingCurve(curveType, &controlPoints);
	}

	UniversalObjectInterface *TinyXmlScmlLoader::getObjectInfoFromTimelineKeyElement(tinyxml2::XMLElement *keyElement, Entity *entity, Object *object, Timeline *timeline, FileFlattener *fileFlattener, SpriteKeyFileInfo *spriteKeyFileInfo, SubEntityKeyInfo *subEntityKeyInfo, point *defaultBoxPivot)
	{
		int spin = 1;
		const tinyxml2::XMLAttribute *spinAtt = findAttributeInElement(keyElement, "spin");
		if (spinAtt)
		{
			spin = spinAtt->IntValue();
		}

		UniversalObjectInterface *objectInfo = 0;
		tinyxml2::XMLElement *objectInfoElement = keyElement->FirstChildElement();
		if (objectInfoElement)
		{
			if (object->getType() == Object::OBJECTTYPE_SPRITE)
			{
				spriteKeyFileInfo->useDefaultPivot = !findAttributeInElement(objectInfoElement, "pivot_x");
				if (spriteKeyFileInfo->useDefaultPivot)
				{
					objectInfo = new BoneObjectInfo();
				}
				else
				{
					objectInfo = new BoxObjectInfo();
				}
			}
			else if (object->getType() == Object::OBJECTTYPE_ENTITY)
			{
				objectInfo = new EntityObjectInfo();
			}
			else
			{
				objectInfo = entity->getNewObjectInfoInstance(object->getId());
			}

			objectInfo->setSpin(spin);
			
			int folder = NO_FILE;
			int file = NO_FILE;
			int entityId = OUT_OF_RANGE;
			int animationIndex = OUT_OF_RANGE;

			point position(0, 0);
			point scale(1, 1);
			point pivot(0, 1);

			if (defaultBoxPivot)
			{
				pivot = *defaultBoxPivot;
			}

			const tinyxml2::XMLAttribute *att = objectInfoElement->FirstAttribute();
			while (att)
			{
				if (equal(att->Name(), "x"))
				{
					position.x = att->DoubleValue();
				}
				else if (equal(att->Name(), "y"))
				{
					position.y = -att->DoubleValue();
				}
				else if (equal(att->Name(), "angle"))
				{
					objectInfo->setAngle(toRadians(360 - att->DoubleValue()));
				}
				else if (equal(att->Name(), "scale_x"))
				{
					scale.x = att->DoubleValue();
				}
				else if (equal(att->Name(), "scale_y"))
				{
					scale.y = att->DoubleValue();
				}
				else if (equal(att->Name(), "pivot_x"))
				{
					pivot.x = att->DoubleValue();
				}
				else if (equal(att->Name(), "pivot_y"))
				{
					pivot.y = 1 - att->DoubleValue();
				}
				else if (equal(att->Name(), "a"))
				{
					objectInfo->setAlpha(att->DoubleValue());
				}
				else if (equal(att->Name(), "folder"))
				{
					folder = att->IntValue();
				}
				else if (equal(att->Name(), "file"))
				{
					file = att->IntValue();
				}
				else if (equal(att->Name(), "entity"))
				{
					entityId = att->IntValue();
				}
				else if (equal(att->Name(), "animation"))
				{
					animationIndex = att->IntValue();
				}
				else if (equal(att->Name(), "t"))
				{
					objectInfo->setTimeRatio(att->DoubleValue());
				}

				objectInfo->setPosition(position);
				objectInfo->setScale(scale);
				objectInfo->setPivot(pivot);
				att = att->Next();
			}

			if (spriteKeyFileInfo)
			{
				spriteKeyFileInfo->fileIndex = fileFlattener->getFlattenedIndex(folder, file);
			}
			else if (subEntityKeyInfo)
			{
				subEntityKeyInfo->entityId = entityId;
				subEntityKeyInfo->animationIndex = animationIndex;
				object->addInitializationId(entityId);
			}

			return objectInfo;
		}
		return 0;
	}

	void TinyXmlScmlLoader::getMainlineFromAnimationElement(tinyxml2::XMLElement *animationElement, Animation *animation, SpriteKeyFileInfoObjectIdMap *spriteKeyFileInfoMap, SubEntityKeyInfoMap *subEntityKeyInfoMap)
	{
		tinyxml2::XMLElement *mainlineElement = animationElement->FirstChildElement("mainline");
		if (mainlineElement)
		{
			tinyxml2::XMLElement *firstKeyElement = mainlineElement->FirstChildElement("key");
			tinyxml2::XMLElement *keyElement = firstKeyElement;
			while (keyElement)
			{
				tinyxml2::XMLElement *nextKeyElement = keyElement->NextSiblingElement();
				MainlineKey *mainlineKey = animation->pushBackMainlineKey(getTimeInfoFromElement(keyElement, nextKeyElement, firstKeyElement, animation->getLength(), animation->getIsLooping()));

				getRefsFromMainlineKeyElement(keyElement, animation, mainlineKey, spriteKeyFileInfoMap, subEntityKeyInfoMap);
				keyElement = keyElement->NextSiblingElement();
			}
		}
	}

	void TinyXmlScmlLoader::getRefsFromMainlineKeyElement(tinyxml2::XMLElement *keyElement, Animation *animation, MainlineKey *mainlineKey, SpriteKeyFileInfoObjectIdMap *spriteKeyFileInfoMap, SubEntityKeyInfoMap *subEntityKeyInfoMap)
	{
		tinyxml2::XMLElement *refElement = keyElement->FirstChildElement();
		std::vector<int> refObjectIds;
		while (refElement)
		{
			const int NOT_FOUND = -1;
			int keyIndex = NOT_FOUND;
			int timelineIndex = NOT_FOUND;
			int objectId = NOT_FOUND;
			int parentObjectId = THIS_ENTITY;

			const tinyxml2::XMLAttribute *att = refElement->FirstAttribute();
			while (att)
			{
				if (equal(att->Name(), "parent"))
				{
					int parentRefIndex = att->IntValue();
					if (parentRefIndex < refObjectIds.size())
					{
						parentObjectId = refObjectIds.at(parentRefIndex);
					}
					else
					{
						// error
						return;
					}
				}
				else if (equal(att->Name(), "timeline"))
				{
					timelineIndex = att->IntValue();
					objectId = animation->getObjectIdFromTimelineIndex(timelineIndex);
					refObjectIds.push_back(objectId);
				}
				else if (equal(att->Name(), "key"))
				{
					keyIndex = att->IntValue();
				}

				att = att->Next();
			}


			if (timelineIndex == NOT_FOUND || keyIndex == NOT_FOUND || objectId == NOT_FOUND)
			{
				// error
				return;
			}

			TimelineKey *timelineKey = animation->getObjectTimelineKey(timelineIndex, keyIndex);
			if (!timelineKey)
			{
				// error
				return;
			}

			if (equal(refElement->Value(), "bone_ref"))
			{
				mainlineKey->pushBackBoneRef(new BoneRef(objectId, parentObjectId, timelineKey));
			}
			else if (equal(refElement->Value(), "object_ref"))
			{
				auto& it = spriteKeyFileInfoMap->find(objectId);
				if (it != spriteKeyFileInfoMap->end())
				{
					SpriteKeyFileInfoVector *spriteKeyInfoVector = &(*it).second;
					if (keyIndex < spriteKeyInfoVector->size())
					{
						SpriteKeyFileInfo *spriteKeyInfo = &spriteKeyInfoVector->at(keyIndex);
						mainlineKey->pushBackZOrderRef(new SpriteRef(objectId, parentObjectId, timelineKey, spriteKeyInfo->fileIndex, spriteKeyInfo->useDefaultPivot));
					}
					else
					{
						// error
						return;
					}
				}
				else
				{
					auto& it = subEntityKeyInfoMap->find(objectId);
					if (it != subEntityKeyInfoMap->end())
					{
						SubEntityKeyInfoVector *subEntityKeyInfoVector = &(*it).second;
						if (keyIndex < subEntityKeyInfoVector->size())
						{
							SubEntityKeyInfo *subEntityKeyInfo = &subEntityKeyInfoVector->at(keyIndex);
							mainlineKey->pushBackZOrderRef(new EntityRef(objectId, parentObjectId, timelineKey, subEntityKeyInfo->entityId, subEntityKeyInfo->animationIndex));
						}
						else
						{
							// error
							return;
						}
					}
					else
					{
						mainlineKey->pushBackZOrderRef(new ObjectRef(objectId, parentObjectId, timelineKey));
					}
				}
			}

			refElement = refElement->NextSiblingElement();
		}
	}

	void TinyXmlScmlLoader::getEventlinesFromAnimationElement(tinyxml2::XMLElement *animationElement, Entity *entity, Animation *animation)
	{
		tinyxml2::XMLElement *eventlineElement = animationElement->FirstChildElement("eventline");
		while (eventlineElement && equal(eventlineElement->Value(), "eventline"))
		{
			std::string timelineName;
			const tinyxml2::XMLAttribute *att = findAttributeInElement(eventlineElement, "name");

			if (att)
			{
				timelineName = att->Value();
			}
			else
			{
				// error
				return;
			}

			Object *object = entity->setObject(timelineName, Object::OBJECTTYPE_TRIGGER);
			Timeline *newTimeline = animation->pushBackTriggerTimeline(object->getId());

			tinyxml2::XMLElement *firstKeyElement = eventlineElement->FirstChildElement("key");
			tinyxml2::XMLElement *keyElement = firstKeyElement;
			while (keyElement)
			{
				tinyxml2::XMLElement *nextKeyElement = keyElement->NextSiblingElement();
				TimeInfo *timeInfo = getTimeInfoFromElement(keyElement, nextKeyElement, firstKeyElement, animation->getLength(), animation->getIsLooping());
				if (!timeInfo)
				{
					// error
					return;
				}

				TimelineKey * newKey = newTimeline->pushBackKey(timeInfo, new TriggerObjectInfo());
				newKey->setNextObjectInfo(newKey->getObjectInfo());

				keyElement = keyElement->NextSiblingElement();
			}

			createRedundantFirstKeys(animation, newTimeline);
			eventlineElement = eventlineElement->NextSiblingElement();
		}
	}

	void TinyXmlScmlLoader::getSoundlinesFromAnimationElement(tinyxml2::XMLElement *animationElement, Entity *entity, Animation *animation, FileFlattener *fileFlattener)
	{
		tinyxml2::XMLElement *soundlineElement = animationElement->FirstChildElement("soundline");
		while (soundlineElement && equal(soundlineElement->Value(), "soundline"))
		{
			std::string timelineName;
			const tinyxml2::XMLAttribute *att = findAttributeInElement(soundlineElement, "name");
			if (att)
			{
				timelineName = att->Value();
			}
			else
			{
				// error
				return;
			}

			Object *object = entity->setObject(timelineName, Object::OBJECTTYPE_SOUND);
			Timeline *newTimeline = animation->pushBackSoundTimeline(object->getId());

			TimelineKey *firstKey = 0;
			TimelineKey *previousKey = 0;

			bool soundFileFound = false;

			tinyxml2::XMLElement *firstKeyElement = soundlineElement->FirstChildElement("key");
			tinyxml2::XMLElement *keyElement = firstKeyElement;
			while (keyElement)
			{
				tinyxml2::XMLElement *nextKeyElement = keyElement->NextSiblingElement();
				TimeInfo *timeInfo = getTimeInfoFromElement(keyElement, nextKeyElement, firstKeyElement, animation->getLength(), animation->getIsLooping());

				UniversalObjectInterface *objectInfo = getSoundObjectInfoFromSoundlineKey(keyElement, entity, object, fileFlattener, &soundFileFound);
				if (!objectInfo)
				{
					// error
					return;
				}

				if (timeInfo)
				{
					if (previousKey)
					{
						previousKey->setNextObjectInfo(objectInfo);
					}

					previousKey = newTimeline->pushBackKey(timeInfo, objectInfo);

					if (!firstKey)
					{
						firstKey = previousKey;
					}
				}
				else
				{
					// error
					return;
				}

				keyElement = nextKeyElement;
			}
			if (previousKey)
			{
				if (animation->getIsLooping())
				{
					previousKey->setNextObjectInfo(firstKey->getObjectInfo());
				}
				else
				{
					previousKey->setNextObjectInfo(previousKey->getObjectInfo());
				}
			}

			createRedundantFirstKeys(animation, newTimeline);
			soundlineElement = soundlineElement->NextSiblingElement();
		}
	}

	UniversalObjectInterface *TinyXmlScmlLoader::getSoundObjectInfoFromSoundlineKey(tinyxml2::XMLElement *keyElement, Entity *entity, Object *object, FileFlattener *fileFlattener, bool *soundFileFound)
	{
		tinyxml2::XMLElement *objectInfoElement = keyElement->FirstChildElement();
		if (objectInfoElement)
		{
			UniversalObjectInterface *objectInfo = object->getNewObjectInfoInstance();

			int trigger = 1;
			real volume = 1;
			real panning = 0;

			const tinyxml2::XMLAttribute *att = objectInfoElement->FirstAttribute();
			while (att)
			{
				if (equal(att->Name(), "volume"))
				{
					volume = att->DoubleValue();
				}
				else if (equal(att->Name(), "panning"))
				{
					panning = att->DoubleValue();
				}
				else if (equal(att->Name(), "trigger"))
				{
					trigger = att->IntValue();
				}
				else if (!*soundFileFound&&equal(att->Name(), "folder"))
				{
					int folder = att->IntValue();
					att = att->Next();
					if (equal(att->Name(), "file"))
					{
						object->addInitializationId(fileFlattener->getFlattenedIndex(folder, att->IntValue()));
					}
					else
					{
						// error
						return 0;
					}
				}

				att = att->Next();
			}

			objectInfo->setTriggerCount(trigger);
			objectInfo->setVolume(volume);
			objectInfo->setPanning(panning);

			return objectInfo;
		}
		else
		{
			// error
			return 0;
		}
	}

}









