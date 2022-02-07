#include "Include.h"
#include "Kitty.h"
#include "Game.h"

Kitty::Kitty(World* world, AnimationData* animData)
	: Animable(animData), Object(world, Math::Vector3(0, 0, 0) )
{
	mKittyState		= KITTY_IDLE;

	mHeading		= Math::Degree(0);
	mScale			= Math::Vector3(0.2f, 0.2f, 0.2f);
	
	
	float catWidth	= 0.4f;
	float catHeight	= 0.8f;
	float catLength = 1.6f;
	mPrevPosition	= mPosition;
	mPrevHeading	= mHeading;
	mBoundingBox	= Math::Box3(-catWidth/2, 0, -catLength/2, catWidth/2, catHeight, catLength/2);
	mVelocity		= Math::Vector3();
	mGrounded		= false;
	mLastAnimTime	= 0;
	mStamina		= MAX_STAMINA;
}

Kitty::~Kitty()
{
}

bool Kitty::initialize()
{
	mAnimation->setState("run");

	return true;
}

void Kitty::update(GameTime& gameTime)
{
	if(keys['A']) {
		mVelocity.x -= ACCELERATION * gameTime.deltaTime;
	} else {
		if(mVelocity.x < 0) {
			mVelocity.x += DRAG * gameTime.deltaTime;
			if(mVelocity.x > 0)
				mVelocity.x = 0;
		}
	}

	if(keys['W']) {
		mVelocity.z += ACCELERATION * gameTime.deltaTime;
	} else {
		if(mVelocity.z > 0) {
			mVelocity.z -= DRAG * gameTime.deltaTime;
			if(mVelocity.z < 0)
				mVelocity.z = 0;
		}
	}

	if(keys['D']) {
		mVelocity.x += ACCELERATION * gameTime.deltaTime;
	} else {
		if(mVelocity.x > 0) {
			mVelocity.x -= DRAG * gameTime.deltaTime;
			if(mVelocity.x < 0)
				mVelocity.x = 0;
		}
	}

	if(keys['S']) {
		mVelocity.z -= ACCELERATION * gameTime.deltaTime;
	} else {
		if(mVelocity.z < 0) {
			mVelocity.z += DRAG * gameTime.deltaTime;
			if(mVelocity.z > 0)
				mVelocity.z = 0;
		}
	}

	static bool jumpTriggered = false;
	static float jumpVelocity = 0;
	if(keys[VK_SPACE] && mGrounded && !jumpTriggered) {
		jumpTriggered = true;
		jumpVelocity = JUMP_SPEED_BASE;
	}
	if(jumpTriggered) {
		jumpVelocity += JUMP_SPEED_REFILL * gameTime.deltaTime;
		if(jumpVelocity > JUMP_SPEED_MAX) {
			jumpVelocity = JUMP_SPEED_MAX;
		}
	}
	if(jumpTriggered && (!keys[VK_SPACE] || jumpVelocity == JUMP_SPEED_MAX)) {
		mGrounded = false;
		mVelocity.y += jumpVelocity;
		jumpVelocity = JUMP_SPEED_BASE;
		jumpTriggered = false;
	}

	mVelocity.y -= ACCEL_GRAVITY * gameTime.deltaTime;
	
	if(keys[VK_CONTROL]) {
		mVelocity.x = Math::clamp<float>(mVelocity.x, -MAX_CROUCH_SPEED, MAX_CROUCH_SPEED);		
		mVelocity.z = Math::clamp<float>(mVelocity.z, -MAX_CROUCH_SPEED, MAX_CROUCH_SPEED);
		mKittyState = KITTY_CROUCHING;
	} else if(keys[VK_SHIFT]) {
		mVelocity.x = Math::clamp<float>(mVelocity.x, -MAX_WALK_SPEED, MAX_WALK_SPEED);		
		mVelocity.z = Math::clamp<float>(mVelocity.z, -MAX_WALK_SPEED, MAX_WALK_SPEED);
		mKittyState = KITTY_WALKING;
	} else {
		mVelocity.x = Math::clamp<float>(mVelocity.x, -MAX_STRAFE_SPEED, MAX_STRAFE_SPEED);		
		mVelocity.z = Math::clamp<float>(mVelocity.z, -MAX_RUN_SPEED, MAX_RUN_SPEED);
	}

	mVelocity.y = Math::clamp<float>(mVelocity.y, -MAX_FALL_SPEED, 999999);

	float headingRad = mHeading.getRadians();
	
	if(mVelocity.x != 0) {
		mPosition.x += mVelocity.x * -sin(headingRad + Math::Degree(90).getRadians()) * gameTime.deltaTime;
		mPosition.z += mVelocity.x * cos(headingRad + Math::Degree(90).getRadians()) * gameTime.deltaTime;
	}

	if(mVelocity.y != 0) {
		mPosition.y += mVelocity.y * gameTime.deltaTime;
	}

	if(mVelocity.z != 0) {
		mPosition.x += mVelocity.z * sin(headingRad) * gameTime.deltaTime;
		mPosition.z += mVelocity.z * -cos(headingRad) * gameTime.deltaTime;
	}

	updateStamina(gameTime);

	updateAnimation(gameTime);

	updateCollisions(gameTime);

	if(mVelocity.y != 0) {
		mGrounded = false;
	}

	mPrevPosition	= mPosition;
	mPrevHeading	= mHeading;
}

void Kitty::draw()
{
	Model* model = mAnimation->getModel();
	Texture* texture = mAnimation->getTexture();
	if(model && texture) {
		
		glPushMatrix();

			glPushMatrix();
				glScalef(mScale.x, mScale.y, mScale.z);
				if(mKittyState == KITTY_CROUCHING) {
					glScalef(1, 0.5f, 1);
				}
				glBindTexture(GL_TEXTURE_2D, texture->getId());
				glCallList(model->getId());
				glBindTexture(GL_TEXTURE_2D, 0);
			glPopMatrix();

			/*
			mBoundingBox.draw(0, 1, 0);
			
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);
						
			float halfHeight = mBoundingBox.getHeight() * 0.5f;
			glLineWidth(3.0f);
			glColor3f(1, 0, 0);
			glBegin(GL_LINES);				
				glVertex3f(0, halfHeight, 0); glVertex3f(-mVelocity.x * 0.5f, halfHeight + mVelocity.y* 0.5f, -mVelocity.z* 0.5f);
			glEnd();
			
			glEnable(GL_LIGHTING);
			glEnable(GL_DEPTH_TEST);
			*/
		glPopMatrix();

	}
}

void Kitty::setHeading(Math::Degree& heading)
{
	mHeading = heading;
	while(mHeading >= 360) {
		mHeading -= 360.0f;
	}
	while(mHeading < 0) {
		mHeading += 360.0f;
	}
}

Math::Vector3& Kitty::getPosition()
{ 
	return mPosition;
}

Math::Degree& Kitty::getHeading()
{
	return mHeading;
}	

Math::Vector3& Kitty::getVelocity()
{
	return mVelocity;
}

float Kitty::getStamina()
{
	return mStamina;
}

void Kitty::updateAnimation(GameTime& gameTime)
{
	//RUNNING ANIMATION
	if(gameTime.timeElapsed > mLastAnimTime + 1/max(abs(mVelocity.z), abs(mVelocity.x)) * 0.5f) {

		mAnimation->incFrame();

		mLastAnimTime = gameTime.timeElapsed;
	}
}

void Kitty::updateStamina(GameTime& gameTime)
{
	//DECREASE STAMINA
	mStamina -= max(abs(mVelocity.z), abs(mVelocity.x)) * 0.1f * gameTime.deltaTime + FATIGUE_RATE * gameTime.deltaTime;
	if(mStamina <= 0) {
	
		mStamina = 0;
	}
}

void Kitty::updateCollisions(GameTime& gameTime)
{
	//check collision with ground
	if(mPosition.y <= 0) {
		mPosition.y = 0;
		mVelocity.y = 0;
		mGrounded = true;
	}

	float halfHeight = mBoundingBox.getHeight() * 0.5f;
	float halfWidth = mBoundingBox.getWidth() * 0.5f;
	float halfLength = mBoundingBox.getLength() * 0.5f;

	float headingDeg = mHeading.getValue();
	float headingRad = mHeading.getRadians();

	float prevHeadingRad = mPrevHeading.getRadians();


	Math::Vector3 PT;
	Math::Vector3 prevPT;

	Column* colPT;									//column of PT	
	StaticObject* obj;								//object collided with by PT

	//------------------------- FRONT POINT	
	PT.x = mPosition.x + halfLength * sin(headingRad);
	PT.y = mPosition.y + halfHeight;
	PT.z = mPosition.z - halfLength * cos(headingRad);

	prevPT.x = mPrevPosition.x + halfLength * sin(prevHeadingRad);
	prevPT.y = mPrevPosition.y + halfHeight;
	prevPT.z = mPrevPosition.z - halfLength * cos(prevHeadingRad);
	updatePointCollision(PT, prevPT);
	
	//------------------------- RIGHT POINT	
	PT.x = mPosition.x - halfWidth * sin(headingRad + Math::Degree(90).getRadians());
	PT.y = mPosition.y + halfHeight;
	PT.z = mPosition.z + halfWidth * cos(headingRad + Math::Degree(90).getRadians());
	prevPT.x = mPrevPosition.x - halfWidth * sin(prevHeadingRad + Math::Degree(90).getRadians());
	prevPT.y = mPrevPosition.y + halfHeight;
	prevPT.z = mPrevPosition.z + halfWidth * cos(prevHeadingRad + Math::Degree(90).getRadians());
	updatePointCollision(PT, prevPT);

	//------------------------- LEFT POINT	
	PT.x = mPosition.x + halfWidth * sin(headingRad + Math::Degree(90).getRadians());
	PT.y = mPosition.y + halfHeight;
	PT.z = mPosition.z - halfWidth * cos(headingRad + Math::Degree(90).getRadians());
	prevPT.x = mPrevPosition.x + halfWidth * sin(prevHeadingRad + Math::Degree(90).getRadians());
	prevPT.y = mPrevPosition.y + halfHeight;
	prevPT.z = mPrevPosition.z - halfWidth * cos(prevHeadingRad + Math::Degree(90).getRadians());
	updatePointCollision(PT, prevPT);

	//------------------------- BACK POINT	
	PT.x = mPosition.x - halfLength * sin(headingRad);
	PT.y = mPosition.y + halfHeight;
	PT.z = mPosition.z + halfLength * cos(headingRad);
	prevPT.x = mPrevPosition.x - halfLength * sin(prevHeadingRad);
	prevPT.y = mPrevPosition.y + halfHeight;
	prevPT.z = mPrevPosition.z + halfLength * cos(prevHeadingRad);
	updatePointCollision(PT, prevPT);

	//------------------------- BOTTOM POINT	
	PT.x = mPosition.x;
	PT.y = mPosition.y;
	PT.z = mPosition.z;

	colPT = mWorld->getColumnFromPt(PT);
	obj = colPT->checkCollisions(PT);
	if(obj) {
		mPosition.y = obj->getPosition().y + obj->getCollisionHeight() + COLLIDE_EPSILON;
		mVelocity.y = 0;
		mGrounded = true;
	}

	//------------------------- TOP POINT
	PT.x = mPosition.x;
	PT.y = mPosition.y + mBoundingBox.getHeight();
	PT.z = mPosition.z;

	colPT = mWorld->getColumnFromPt(PT);
	obj = colPT->checkCollisions(PT);
	if(obj) {
		mPosition.y = obj->getPosition().y - mBoundingBox.getHeight() - COLLIDE_EPSILON;
		mVelocity.y = 0;
	}
}

void Kitty::updatePointCollision(Math::Vector3& PT, Math::Vector3& prevPT)
{
	Column* colPT;									//column of PT
	Column* colPrevPT;								//column of prevPT
	StaticObject* obj;								//object collided with by PT

	obj = mWorld->checkCollisions(PT);

	//if collision has occured at PT
	if(obj) {		

		//get prevPT column
		colPT		= mWorld->getColumnFromPt(PT);
		colPrevPT	= mWorld->getColumnFromPt(prevPT);

		//get edges of PT column
		float colUnitLeft	= colPT->getUnitLeft();	
		float colUnitRight	= colPT->getUnitRight();
		float colUnitFront	= colPT->getUnitFront();
		float colUnitBack	= colPT->getUnitBack();

		//check neighbor objects
		StaticObject* occLeft	= mWorld->checkCollisions( Math::Vector3( colUnitLeft - COLLIDE_EPSILON, PT.y, PT.z ) );
		StaticObject* occRight	= mWorld->checkCollisions( Math::Vector3( colUnitRight + COLLIDE_EPSILON, PT.y, PT.z ) );		
		StaticObject* occFront	= mWorld->checkCollisions( Math::Vector3( PT.x, PT.y, colUnitFront - COLLIDE_EPSILON ) );
		StaticObject* occBack	= mWorld->checkCollisions( Math::Vector3( PT.x, PT.y, colUnitBack + COLLIDE_EPSILON ) );

		//prevent double-collision with x-axis and z-axis
		bool collided = false;

		//if collision on left wall
		//			|   |
		//		____|___|____
		//		  . | . |
		//		____|___|____
		//			|   |
		//			|   |
		if(colPrevPT->getTileX() < colPT->getTileX()) {
			float deltaX = PT.x - colUnitLeft + COLLIDE_EPSILON;	
			if(!occLeft) {							
				mPosition.x -= deltaX;
				collided = true;
			} else {
				//occLeft == true
				
				//if collision from down left (corner)
				//			|   |
				//		____|___|____
				//		    | . |
				//		____|___|____
				//		  . |   |
				//			|   |
				if(colPrevPT->getTileZ() < colPT->getTileZ()) {
					if(occFront) {
						float deltaZ = PT.z - colUnitFront + COLLIDE_EPSILON;						
						mPosition.x -= deltaX;
						mPosition.z -= deltaZ;
						mVelocity = Math::Vector3(0, mVelocity.y, 0);
						collided = true;
					}
				} else {
					//else collision from up left (corner)	
					//		  . |   |
					//		____|___|____
					//		    | . |
					//		____|___|____
					//		    |   |
					//			|   |
					if(occBack) {				
						float deltaZ = colUnitBack - PT.z + COLLIDE_EPSILON;
						mPosition.x -= deltaX;
						mPosition.z += deltaZ;						
						mVelocity = Math::Vector3(0, mVelocity.y, 0);
						collided = true;						
					}
				}
			}
		}
		//else if collision on right wall
		//		    |   |
		//		____|___|____
		//		    | . | .
		//		____|___|____
		//		    |   |
		//			|   |
		else if(colPrevPT->getTileX() > colPT->getTileX()) {
			float deltaX = colUnitRight - PT.x + COLLIDE_EPSILON;		
			if(!occRight) {						
				mPosition.x += deltaX;
				collided = true;
			} else {
				//occRight == true

				//if collision from down right (corner)
				//		    |   |
				//		____|___|____
				//		    | . | 
				//		____|___|____
				//		    |   | .
				//			|   |
				if(colPrevPT->getTileZ() < colPT->getTileZ()) {					
					if(occFront) {
						float deltaZ = PT.z - colUnitFront + COLLIDE_EPSILON;						
						mPosition.x += deltaX;
						mPosition.z -= deltaZ;						
						mVelocity = Math::Vector3(0, mVelocity.y, 0);						
						collided = true;
					}
				} else {
					//if collision from up right (corner)
					//		    |   | .
					//		____|___|____
					//		    | . | 
					//		____|___|____
					//		    |   |
					//			|   |
					if(occBack) {
						float deltaZ = colUnitBack - PT.z + COLLIDE_EPSILON;
						mPosition.x += deltaX;
						mPosition.z += deltaZ;						
						mVelocity = Math::Vector3(0, mVelocity.y, 0);			
						collided = true;
					}
				}




			} //end else occRight == true

		}
		//else if collision is occuring from same block
		//		    |   |
		//		____|___|____
		//		    | ..| 
		//		____|___|____
		//		    |   |
		//			|   |
		else if(colPrevPT == colPT) {
	
			//get column at cat's position
			Column* catCol = mWorld->getColumnFromPt(mPosition);
			
			//if cat is on left side of PT
			if(catCol->getTileX() < colPT->getTileX()) {
				float deltaX = PT.x - colUnitLeft + COLLIDE_EPSILON;				
				mPosition.x -= deltaX;
				mVelocity = Math::Vector3(0, mVelocity.y, 0);
				collided = true;				
			}	//else if cat is on right side of PT
			else if( catCol->getTileX() > colPT->getTileX() ) {
				float deltaX = colUnitRight - PT.x + COLLIDE_EPSILON;				
				mPosition.x += deltaX;
				mVelocity = Math::Vector3(0, mVelocity.y, 0);
				collided = true;
			}
			
			catCol = mWorld->getColumnFromPt(mPosition);

			//if cat is on the front side of PT
			if( catCol->getTileZ() < colPT->getTileZ() ) {				
				float deltaZ = PT.z - colUnitFront + COLLIDE_EPSILON;
				mPosition.z -= deltaZ;
				mVelocity = Math::Vector3(0, mVelocity.y, 0);
				collided = true;
			}	//if cat is on back side of PT
			else if( catCol->getTileZ() > colPT->getTileZ() ) {
				float deltaZ = colUnitBack - PT.z + COLLIDE_EPSILON;
				mPosition.z += deltaZ;
				mVelocity = Math::Vector3(0, mVelocity.y, 0);
				collided = true;
			}

		} // end else if(colPrevPT == colPT)


		//if collision has not occured yet
		if(!collided) {
			//if collision on front wall
			//		    |   |
			//		____|___|____
			//		    | . | 
			//		____|___|____
			//		    | . |
			//			|   |
			if(colPrevPT->getTileZ() < colPT->getTileZ()) {
				float deltaZ = PT.z - colUnitFront + COLLIDE_EPSILON;
				mPosition.z -= deltaZ;
				collided = true;
			}	//else if collision on back wall
			//		    | . |
			//		____|___|____
			//		    | . | 
			//		____|___|____
			//		    |   |
			//			|   |
			else if(colPrevPT->getTileZ() > colPT->getTileZ()) {
				float deltaZ = colUnitBack - PT.z + COLLIDE_EPSILON;
				mPosition.z += deltaZ;
				collided = true;
			}

		} //end if(!collided)


	}//if obj



		/*
		//if collision on left wall
		//			|   |
		//		____|___|____
		//		  . | . |
		//		____|___|____
		//			|   |
		//			|   |
		if(colPrevPT->getTileX() < colPT->getTileX()) {
			float deltaX = PT.x - colUnitLeft + COLLIDE_EPSILON;
			if(!occLeft) {
				mPosition.x -= deltaX;
				collided = true; 
			} else {
				//occLeft == true
				
				//if collision from down left (corner)
				//			|   |
				//		____|___|____
				//		    | . |
				//		____|___|____
				//		  . |   |
				//			|   |
				if(colPrevPT->getTileZ() < colPT->getTileZ()) {
					if(occFront) {
						float deltaZ = PT.z - colUnitFront + COLLIDE_EPSILON;
						
						mPosition.x -= deltaX;
						mPosition.z -= deltaZ;

						mVelocity = Math::Vector3(0, mVelocity.y, 0);

						collided = true;
					}
				} else {
					//else collision from up left (corner)	
					//		  . |   |
					//		____|___|____
					//		    | . |
					//		____|___|____
					//		    |   |
					//			|   |
					if(occBack) {				
						float deltaZ = colUnitBack - PT.z + COLLIDE_EPSILON;

						mPosition.x -= deltaX;
						mPosition.z += deltaZ;
						
						mVelocity = Math::Vector3(0, mVelocity.y, 0);

						collided = true;						
					}
				}
			}
		}
		//else if collision on right wall
		//		    |   |
		//		____|___|____
		//		    | . | .
		//		____|___|____
		//		    |   |
		//			|   |
		else if(colPrevPT->getTileX() > colPT->getTileX()) {
			
			float deltaX = colUnitRight - PT.x + COLLIDE_EPSILON;
			if(!occRight) {
				mPosition.x += deltaX;
				collided = true;				
			} else {
				//occRight == true

				//if collision from down right (corner)
				//		    |   |
				//		____|___|____
				//		    | . | 
				//		____|___|____
				//		    |   | .
				//			|   |
				if(colPrevPT->getTileZ() < colPT->getTileZ()) {					
					if(occFront) {
						float deltaZ = PT.z - colUnitFront + COLLIDE_EPSILON;
						
						mPosition.x += deltaX;
						mPosition.z -= deltaZ;
						
						mVelocity = Math::Vector3(0, mVelocity.y, 0);
						
						collided = true;
					}
				} else {
					//if collision from up right (corner)
					//		    |   | .
					//		____|___|____
					//		    | . | 
					//		____|___|____
					//		    |   |
					//			|   |
					if(occBack) {
						float deltaZ = colUnitBack - PT.z + COLLIDE_EPSILON;

						mPosition.x += deltaX;
						mPosition.z += deltaZ;
						
						mVelocity = Math::Vector3(0, mVelocity.y, 0);			

						collided = true;
					}
				}
			}

		}
		//else if collision is occuring from same block
		//		    |   |
		//		____|___|____
		//		    | ..| 
		//		____|___|____
		//		    |   |
		//			|   |
		else if(colPrevPT == colPT) {
	
			//get column at cat's position
			Column* catCol = mWorld->getColumnFromPt(mPosition);
			
			//if cat is on left side of PT
			if(catCol->getTileX() < colPT->getTileX()) {
				float deltaX = PT.x - colUnitLeft + COLLIDE_EPSILON;
				
				mPosition.x -= deltaX;

				mVelocity = Math::Vector3(0, mVelocity.y, 0);

				collided = true;
				
			}	//if cat is on right side of PT
			else if( catCol->getTileX() > colPT->getTileX() ) {

				float deltaX = colUnitRight - PT.x + COLLIDE_EPSILON;
				
				mPosition.x += deltaX;

				mVelocity = Math::Vector3(0, mVelocity.y, 0);

				collided = true;
			}
			
			//if cat is on the front side of PT
			if( catCol->getTileZ() < colPT->getTileZ() ) {
				
				float deltaZ = PT.z - colUnitFront + COLLIDE_EPSILON;

				mPosition.z -= deltaZ;

				mVelocity = Math::Vector3(0, mVelocity.y, 0);

				collided = true;

			}	//if cat is on back side of PT
			else if( catCol->getTileZ() > colPT->getTileZ() ) {

				float deltaZ = colUnitBack - PT.z + COLLIDE_EPSILON;

				mPosition.z += deltaZ;

				mVelocity = Math::Vector3(0, mVelocity.y, 0);

				collided = true;
			}
		}

		//if collision has not occured yet
		if(!collided) {

			//if collision on bottom wall
			//		    |   |
			//		____|___|____
			//		    | . | 
			//		____|___|____
			//		    | . |
			//			|   |
			if(colPrevPT->getTileZ() < colPT->getTileZ()) {
				float deltaZ = PT.z - colUnitFront + COLLIDE_EPSILON;

				mPosition.z -= deltaZ;

				collided = true;

			}	//else if collision on top wall
			//		    | . |
			//		____|___|____
			//		    | . | 
			//		____|___|____
			//		    |   |
			//			|   |
			else if(colPrevPT->getTileZ() > colPT->getTileZ()) {
				float deltaZ = colUnitBack - PT.z + COLLIDE_EPSILON;

				mPosition.z += deltaZ;

				collided = true;
			}

		}

	}
	*/


}