#pragma once

// cstdlib

// external libs


// program
#include "PCH.h"
#include "ParticleSettings.h"
#include "Transform.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Utils.h"

#define MAX_PARTICLES 10000

namespace SnowGL
{
	/*! @class Particle
	*	@brief The data for a particle in the Snowfall System
	*
	*	A particle data class which contains only the data for managing particles, not rendering.
	*/
	struct Particle
	{
		glm::vec4	currentPosition;	/**< The particle position */
		glm::vec4	startPosition;		/**< The particle position */
		glm::vec3	velocity;			/**< The particle velocity */
		float		delay		= -1;	/**< The particles delay from the start of the simulation to when it is created */
		float		lifetime	= -1;	/**< The particles lifetime */
	};

	/*! @class SnowfallSystem
	*	@brief The management system for simulating snowfall
	*
	*	The snowfall system simulates particles through Transform Feedback with OpenGL.
	// TODO: Expand
	*/
	class ParticleSystem
	{
	public:
		/** @brief Snowfall System Ctor
		*
		*	Nothing
		*/
		ParticleSystem(const ParticleSettings &_settings);
		/** @brief Snowfall System Dtor
		*
		*	Nothing
		*/
		~ParticleSystem();

		/** @brief Initialises the Snowfall System
		*
		*	Initialises the buffers and shaders for Transform Feedback
		*/
		bool initialise();

		/** @brief Applys settings to the shader
		*
		*	Takes the stored settings CPU side and applies them to the GPU based shader for the particles.
		*/
		void applySettingsToShader();

		/** @brief Renderer Ctor
		*	@param _deltaTime The update deltaTime
		*
		*	Performs the transform feedback operation for simulating particles
		*/
		void updateParticles(float _deltaTime);
		/** @brief Renderer Ctor
		*	@param _deltaTime The update deltaTime
		// TODO: Particle Renderer
		*
		*	Performs the transform feedback operation for simulating particles
		*/
		void render(int _deltaTime, const glm::mat4 & _VP, const glm::vec3 & _cameraPos);

		/** @brief Gets the partcle settings
		*	@return A pointer to the particles settings
		*
		*	Returns a pointer to the particles settings which can be modified and then pushed to the GPU using the applySettingsToShader
		*	method, also on this class.
		*/
		inline std::shared_ptr<ParticleSettings> getSettingsPtr() { return m_settings; }

	protected:
		// TODO: doxygen
		void renderParticles(const glm::mat4 & _VP, const glm::vec3 & _cameraPos);

		std::shared_ptr<ParticleSettings>	m_settings;

		bool								m_isFirstRender;		/**< Flag for if this is the first render */			
		unsigned int						m_currVAO;				/**< The current Transform Feedback Buffer */
		unsigned int						m_currVBO;				/**< The current Vertex Buffer */
		std::shared_ptr<VertexArray>		m_tfVAO[2];				/**< The Vertex Arrays for particle data */
		std::shared_ptr<VertexBuffer>		m_tfVBO[2];				/**< The Vertex Buffers for particle data */

		std::shared_ptr<ShaderProgram>		m_tfShader;				/**< The transform Feedback shader */

		int									m_numParticles;			/**< THe number of particles */

		int									m_frameCount = 0;
		float								m_simTime = 0;

		Transform							m_transform;
	};
}