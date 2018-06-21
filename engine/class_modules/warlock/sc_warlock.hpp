#pragma once
#include "simulationcraft.hpp"

namespace warlock
{
    struct warlock_t;

    namespace pets {
      struct warlock_pet_t;
      namespace dreadstalker {
        struct dreadstalker_t;
      }
      namespace wild_imp {
        struct wild_imp_pet_t;
      }
      namespace vilefiend {
        struct vilefiend_t;
      }
      namespace demonic_tyrant {
        struct demonic_tyrant_t;
      }
      namespace infernal {
        struct infernal_t;
      }
      namespace shivarra {
        struct shivarra_t;
      }
      namespace darkhound {
        struct darkhound_t;
      }
      namespace bilescourge {
        struct bilescourge_t;
      }
      namespace urzul {
        struct urzul_t;
      }
      namespace void_terror {
        struct void_terror_t;
      }
      namespace wrathguard {
        struct wrathguard_t;
      }
      namespace vicious_hellhound {
        struct vicious_hellhound_t;
      }
      namespace illidari_satyr {
        struct illidari_satyr_t;
      }
      namespace eyes_of_guldan {
        struct eyes_of_guldan_t;
      }
      namespace prince_malchezaar {
        struct prince_malchezaar_t;
      }

      namespace darkglare
      {
        struct darkglare_t;
      }
    }

    constexpr int MAX_UAS = 5;

    struct warlock_td_t : public actor_target_data_t
    {
      propagate_const<dot_t*> dots_drain_life;
      
      //Aff
      propagate_const<dot_t*> dots_agony;
      propagate_const<dot_t*> dots_corruption;
      propagate_const<dot_t*> dots_seed_of_corruption;
      std::array<propagate_const<dot_t*>, MAX_UAS> dots_unstable_affliction;
      propagate_const<dot_t*> dots_drain_soul;
      propagate_const<dot_t*> dots_siphon_life;
      propagate_const<dot_t*> dots_phantom_singularity;
      propagate_const<dot_t*> dots_vile_taint;

      propagate_const<buff_t*> debuffs_haunt;
      propagate_const<buff_t*> debuffs_agony;
      propagate_const<buff_t*> debuffs_shadow_embrace;
      propagate_const<buff_t*> debuffs_tormented_agony;

      //Destro
      propagate_const<dot_t*> dots_immolate;
      propagate_const<dot_t*> dots_channel_demonfire;
      propagate_const<dot_t*> dots_roaring_blaze;

      propagate_const<buff_t*> debuffs_shadowburn;
      propagate_const<buff_t*> debuffs_eradication;
      propagate_const<buff_t*> debuffs_roaring_blaze;
      propagate_const<buff_t*> debuffs_havoc;
      propagate_const<buff_t*> debuffs_chaotic_flames;
      
      //Demo
      propagate_const<dot_t*> dots_doom;

      propagate_const<buff_t*> debuffs_from_the_shadows;
      propagate_const<buff_t*> debuffs_jaws_of_shadow;

      int agony_stack;
      double soc_threshold;

      warlock_t& warlock;
      warlock_td_t( player_t* target, warlock_t& p );

      void reset()
      {
        agony_stack = 1;
        soc_threshold = 0;
      }

      void target_demise();
    };

    struct warlock_t : public player_t
    {
    public:
      player_t * havoc_target;
      double agony_accumulator;

      // Active Pet
      struct pets_t
      {
        pets::warlock_pet_t* active;
        pets::warlock_pet_t* last;
        static const int WILD_IMP_LIMIT = 40;
        static const int DREADSTALKER_LIMIT = 4;
        static const int VILFIEND_LIMIT = 1;
        static const int DEMONIC_TYRANT_LIMIT = 1;
        static const int INFERNAL_LIMIT = 1;
        static const int RANDOM_LIMIT = 10;
        static const int RARE_RANDOM_LIMIT = 10;
        static const int DARKGLARE_LIMIT = 1;
        std::array<pets::wild_imp::wild_imp_pet_t*, WILD_IMP_LIMIT> wild_imps;
        std::array<pets::dreadstalker::dreadstalker_t*, DREADSTALKER_LIMIT> dreadstalkers;
        std::array<pets::vilefiend::vilefiend_t*, VILFIEND_LIMIT> vilefiends;
        std::array<pets::demonic_tyrant::demonic_tyrant_t*, DEMONIC_TYRANT_LIMIT> demonic_tyrants;
        std::array<pets::infernal::infernal_t*, INFERNAL_LIMIT> infernals;
        std::array<pets::shivarra::shivarra_t*, RANDOM_LIMIT> shivarra;
        std::array<pets::darkhound::darkhound_t*, RANDOM_LIMIT> darkhounds;
        std::array<pets::bilescourge::bilescourge_t*, RANDOM_LIMIT> bilescourges;
        std::array<pets::urzul::urzul_t*, RANDOM_LIMIT> urzuls;
        std::array<pets::void_terror::void_terror_t*, RANDOM_LIMIT> void_terrors;
        std::array<pets::wrathguard::wrathguard_t*, RANDOM_LIMIT> wrathguards;
        std::array<pets::vicious_hellhound::vicious_hellhound_t*, RANDOM_LIMIT> vicious_hellhounds;
        std::array<pets::illidari_satyr::illidari_satyr_t*, RANDOM_LIMIT> illidari_satyrs;
        std::array<pets::eyes_of_guldan::eyes_of_guldan_t*, 4> eyes_of_guldan;
        std::array<pets::prince_malchezaar::prince_malchezaar_t*, RARE_RANDOM_LIMIT> prince_malchezaar;
        std::array<pets::darkglare::darkglare_t*, DARKGLARE_LIMIT> darkglare;
      } warlock_pet_list;

      std::vector<std::string> pet_name_list;

      struct active_t
      {
        action_t* grimoire_of_sacrifice_proc;
        action_t* cry_havoc;
        action_t* tormented_agony;
        action_t* chaotic_flames;
        spell_t* corruption;
        spell_t* roaring_blaze;
        spell_t* internal_combustion;
        spell_t* rain_of_fire;
        spell_t* bilescourge_bombers;
        spell_t* summon_random_demon;
        melee_attack_t* soul_strike;
      } active;

      // Talents
      struct talents_t
      {
        // shared
        // tier 45
        const spell_data_t* demon_skin;
        const spell_data_t* burning_rush;
        const spell_data_t* dark_pact;
        // tier 75
        const spell_data_t* darkfury;
        const spell_data_t* mortal_coil;
        const spell_data_t* demonic_circle;
        // tier 90
        const spell_data_t* grimoire_of_sacrifice; // aff and destro
        // tier 100
        const spell_data_t* soul_conduit;
        // AFF
        const spell_data_t* nightfall;
        const spell_data_t* drain_soul;
        const spell_data_t* haunt;

        const spell_data_t* writhe_in_agony;
        const spell_data_t* absolute_corruption;
        const spell_data_t* siphon_life;

        const spell_data_t* sow_the_seeds;
        const spell_data_t* phantom_singularity;
        const spell_data_t* vile_taint;

        const spell_data_t* shadow_embrace;
        const spell_data_t* deathbolt;
        // grimoire of sacrifice

        // soul conduit
        const spell_data_t* creeping_death;
        const spell_data_t* dark_soul_misery;
        
        // DEMO
        const spell_data_t* dreadlash;
        const spell_data_t* demonic_strength;
        const spell_data_t* bilescourge_bombers;

        const spell_data_t* demonic_calling;
        const spell_data_t* power_siphon;
        const spell_data_t* doom;
        
        const spell_data_t* from_the_shadows;
        const spell_data_t* soul_strike;
        const spell_data_t* summon_vilefiend;
        
        const spell_data_t* inner_demons;
        const spell_data_t* grimoire_felguard;

        const spell_data_t* sacrificed_souls;
        const spell_data_t* demonic_consumption;
        const spell_data_t* nether_portal;
        // DESTRO
        const spell_data_t* flashover;
        const spell_data_t* eradication;
        const spell_data_t* soul_fire;

        const spell_data_t* reverse_entropy;
        const spell_data_t* internal_combustion;
        const spell_data_t* shadowburn;

        const spell_data_t* inferno;
        const spell_data_t* fire_and_brimstone;
        const spell_data_t* cataclysm;

        const spell_data_t* roaring_blaze;
        const spell_data_t* grimoire_of_supremacy;

        const spell_data_t* channel_demonfire;
        const spell_data_t* dark_soul_instability;
      } talents;

      struct legendary_t
      {
        const spell_data_t* odr_shawl_of_the_ymirjar;
        bool feretory_of_souls;
        bool wilfreds_sigil_of_superior_summoning_flag;
        bool stretens_insanity;
        timespan_t wilfreds_sigil_of_superior_summoning;
        double power_cord_of_lethtendris_chance;
        bool wakeners_loyalty_enabled;
        bool lessons_of_spacetime;
        timespan_t lessons_of_spacetime1;
        timespan_t lessons_of_spacetime2;
        timespan_t lessons_of_spacetime3;
        bool sephuzs_secret;
        double sephuzs_passive;
        bool magistrike;
        bool the_master_harvester;
        bool alythesss_pyrogenics;

      } legendary;

      // Mastery Spells
      struct mastery_spells_t
      {
        const spell_data_t* potent_afflictions;
        const spell_data_t* master_demonologist;
        const spell_data_t* chaotic_energies;
      } mastery_spells;

      //Procs and RNG
      propagate_const<real_ppm_t*> affliction_t20_2pc_rppm;
      propagate_const<real_ppm_t*> grimoire_of_sacrifice_rppm; // grimoire of sacrifice

      // Cooldowns
      struct cooldowns_t
      {
        propagate_const<cooldown_t*> haunt;
        propagate_const<cooldown_t*> shadowburn;
        propagate_const<cooldown_t*> soul_fire;
        propagate_const<cooldown_t*> sindorei_spite_icd;
        propagate_const<cooldown_t*> call_dreadstalkers;
      } cooldowns;

      // Passives
      struct specs_t
      {
        // All Specs
        const spell_data_t* fel_armor;
        const spell_data_t* nethermancy;

        // Affliction only
        const spell_data_t* affliction;
        const spell_data_t* nightfall;
        const spell_data_t* unstable_affliction;
        const spell_data_t* unstable_affliction_2;
        const spell_data_t* agony;
        const spell_data_t* agony_2;
        const spell_data_t* shadow_bite;
        const spell_data_t* shadow_bite_2;
        const spell_data_t* shadow_bolt; // also demo
        const spell_data_t* summon_darkglare;

        // Demonology only
        const spell_data_t* demonology;
        const spell_data_t* doom;
        const spell_data_t* wild_imps;
        const spell_data_t* demonic_core;

        // Destruction only
        const spell_data_t* destruction;
        const spell_data_t* immolate;
        const spell_data_t* conflagrate;
        const spell_data_t* conflagrate_2;
        const spell_data_t* unending_resolve;
        const spell_data_t* unending_resolve_2;
        const spell_data_t* firebolt;
        const spell_data_t* firebolt_2;
      } spec;

      // Buffs
      struct buffs_t
      {
        propagate_const<buff_t*> demonic_power;
        propagate_const<buff_t*> grimoire_of_sacrifice;

        //affliction buffs
        propagate_const<buff_t*> active_uas;
        propagate_const<buff_t*> nightfall;
        propagate_const<buff_t*> dark_soul_misery;
        propagate_const<buff_t*> demonic_speed; // t20 4pc

        //demonology buffs
        propagate_const<buff_t*> demonic_core;
        propagate_const<buff_t*> demonic_calling;
        propagate_const<buff_t*> inner_demons;
        propagate_const<buff_t*> nether_portal;
        propagate_const<buff_t*> dreaded_haste; // t20 4pc
        propagate_const<buff_t*> rage_of_guldan; // t21 2pc
        propagate_const<buff_t*> wild_imps;
        propagate_const<buff_t*> dreadstalkers;
        propagate_const<buff_t*> vilefiend;
        propagate_const<buff_t*> tyrant;
        propagate_const<buff_t*> portal_summons;
        propagate_const<buff_t*> grimoire_felguard;
        propagate_const<buff_t*> prince_malchezaar;
        propagate_const<buff_t*> eyes_of_guldan;

        //destruction_buffs
        propagate_const<buff_t*> backdraft;
        propagate_const<buff_t*> embrace_chaos;
        propagate_const<buff_t*> active_havoc;
        propagate_const<buff_t*> reverse_entropy;
        propagate_const<buff_t*> grimoire_of_supremacy;
        propagate_const<buff_t*> dark_soul_instability;

        // legendary buffs
        buff_t* sindorei_spite;
        propagate_const<buff_t*> stretens_insanity;
        propagate_const<buff_t*> lessons_of_spacetime;
        propagate_const<haste_buff_t*> sephuzs_secret;
        propagate_const<buff_t*> alythesss_pyrogenics;
        propagate_const<buff_t*> wakeners_loyalty;
      } buffs;

      // Gains
      struct gains_t
      {
        gain_t* soul_conduit;

        gain_t* agony;
        gain_t* drain_soul;
        gain_t* seed_of_corruption;
        gain_t* unstable_affliction_refund;

        gain_t* conflagrate;
        gain_t* shadowburn;
        gain_t* incinerate;
        gain_t* incinerate_crits;
        gain_t* fnb_bits;
        gain_t* immolate;
        gain_t* immolate_crits;
        gain_t* soul_fire;
        gain_t* infernal;
        gain_t* shadowburn_shard;
        gain_t* inferno;
        gain_t* reverse_entropy;

        gain_t* miss_refund;
        
        gain_t* power_trip;
        gain_t* shadow_bolt;
        gain_t* doom;
        
        gain_t* soulsnatcher;
        gain_t* t19_2pc_demonology;

        gain_t* recurrent_ritual;
        gain_t* feretory_of_souls;
        gain_t* power_cord_of_lethtendris;

        gain_t* affliction_t20_2pc;
        gain_t* destruction_t20_2pc;
      } gains;

      // Procs
      struct procs_t
      {
        proc_t* soul_conduit;
        proc_t* the_master_harvester;
        //aff
        proc_t* nightfall;
        proc_t* affliction_t21_2pc;
        //demo
        proc_t* demonic_calling;
        proc_t* power_trip;
        proc_t* souls_consumed;
        proc_t* one_shard_hog;
        proc_t* two_shard_hog;
        proc_t* three_shard_hog;
        proc_t* wild_imp;
        proc_t* fragment_wild_imp;
        proc_t* dreadstalker_debug;
        proc_t* portal_summon;
        proc_t* demonology_t20_2pc;
        //destro
        proc_t* t19_2pc_chaos_bolts;
        proc_t* reverse_entropy;
      } procs;

      struct spells_t
      {
        spell_t* melee;
        spell_t* seed_of_corruption_aoe;
        spell_t* implosion_aoe;
      } spells;

      int initial_soul_shards;
      bool allow_sephuz;
      bool deaths_embrace_fixed_time;
      std::string default_pet;

      timespan_t shard_react;

      warlock_t( sim_t* sim, const std::string& name, race_e r = RACE_UNDEAD );

      // Character Definition
      void      init_spells() override;
      void      init_base_stats() override;
      void      init_scaling() override;
      void      create_buffs() override;
      void      init_gains() override;
      void      init_procs() override;
      void      init_rng() override;
      void      init_action_list() override;
      void      init_resources( bool force ) override;
      void      reset() override;
      void      create_options() override;
      action_t* create_action( const std::string& name, const std::string& options ) override;
      bool create_actions() override;
      pet_t*    create_pet( const std::string& name, const std::string& type = std::string() ) override;
      void      create_pets() override;
      std::string      create_profile( save_e ) override;
      void      copy_from( player_t* source ) override;
      resource_e primary_resource() const override { return RESOURCE_MANA; }
      role_e    primary_role() const override { return ROLE_SPELL; }
      stat_e    convert_hybrid_stat( stat_e s ) const override;
      stat_e    primary_stat() const override { return STAT_INTELLECT; }
      double    matching_gear_multiplier( attribute_e attr ) const override;
      double    composite_player_multiplier( school_e school ) const override;
      double    composite_player_target_multiplier( player_t* target, school_e school ) const override;
      double    composite_rating_multiplier( rating_e rating ) const override;
      void      invalidate_cache( cache_e ) override;
      double    composite_spell_crit_chance() const override;
      double    composite_spell_haste() const override;
      double    composite_melee_haste() const override;
      double    composite_melee_crit_chance() const override;
      double    composite_mastery() const override;
      double    resource_gain( resource_e, double, gain_t* = nullptr, action_t* = nullptr ) override;
      double    resource_regen_per_second( resource_e ) const override;
      double    composite_armor() const override;
      void      halt() override;
      void      combat_begin() override;
      expr_t*   create_expression( const std::string& name_str ) override;
      std::string       default_potion() const override;
      std::string       default_flask() const override;
      std::string       default_food() const override;
      std::string       default_rune() const override;


      target_specific_t<warlock_td_t> target_data;

      warlock_td_t* get_target_data( player_t* target ) const override
      {
        warlock_td_t*& td = target_data[target];
        if ( !td )
        {
          td = new warlock_td_t( target, const_cast< warlock_t& >( *this ) );
        }
        return td;
      }

      // sc_warlock_affliction
      action_t* create_action_affliction( const std::string& action_name, const std::string& options_str );
      void create_buffs_affliction();
      void init_spells_affliction();
      void init_gains_affliction();
      void init_rng_affliction();
      void init_procs_affliction();
      void create_options_affliction();
      void create_apl_affliction();
      void legendaries_affliction();

      // sc_warlock_demonology
      action_t* create_action_demonology( const std::string& action_name, const std::string& options_str );
      void create_buffs_demonology();
      void init_spells_demonology();
      void init_gains_demonology();
      void init_rng_demonology();
      void init_procs_demonology();
      void create_options_demonology();
      void create_apl_demonology();
      void legendaries_demonology();

      // sc_warlock_destruction
      action_t* create_action_destruction( const std::string& action_name, const std::string& options_str );
      void create_buffs_destruction();
      void init_spells_destruction();
      void init_gains_destruction();
      void init_rng_destruction();
      void init_procs_destruction();
      void create_options_destruction();
      void create_apl_destruction();
      void legendaries_destruction();

    private:
      void apl_precombat();
      void apl_default();
      void apl_global_filler();
    };

    void parse_spell_coefficient(action_t& a);

    namespace pets {
      struct warlock_pet_t : public pet_t {
        action_t* special_action;
        action_t* special_action_two;
        melee_attack_t* melee_attack;
        stats_t* summon_stats;
        spell_t *ascendance;

        struct buffs_t
        {
          propagate_const<buff_t*> embers;

          propagate_const<buff_t*> the_expendables;
          propagate_const<buff_t*> rage_of_guldan;
          propagate_const<buff_t*> demonic_strength;
          propagate_const<buff_t*> demonic_consumption;
          propagate_const<buff_t*> grimoire_of_service;
        } buffs;

        struct active_t
        {
          melee_attack_t* soul_strike;
          action_t* demonic_strength_felstorm;
          spell_t*        bile_spit;
        } active;

        bool is_demonbolt_enabled = true;
        bool is_lord_of_flames = false;
        bool t21_4pc_reset = false;
        bool is_warlock_pet = true;
        int bites_executed = 0;
        int dreadbite_executes = 0;

        warlock_pet_t( sim_t* sim, warlock_t* owner, const std::string& pet_name, pet_e pt, bool guardian = false );
        void init_base_stats() override;
        void init_action_list() override;
        void create_buffs() override;
        void init_spells() override;
        bool create_actions() override;
        void schedule_ready( timespan_t delta_time = timespan_t::zero(),
          bool   waiting = false ) override;
        double composite_player_multiplier( school_e school ) const override;
        double composite_melee_crit_chance() const override;
        double composite_spell_crit_chance() const override;
        double composite_melee_haste() const override;
        double composite_spell_haste() const override;
        double composite_melee_speed() const override;
        double composite_spell_speed() const override;

        void create_buffs_demonology();
        void init_spells_demonology();

        void create_buffs_destruction();

        resource_e primary_resource() const override { return RESOURCE_ENERGY; }

        warlock_t* o()
        {
          return static_cast<warlock_t*>( owner );
        }
        const warlock_t* o() const
        {
          return static_cast<warlock_t*>( owner );
        }

        void trigger_sephuzs_secret( const action_state_t* state, spell_mechanic mechanic )
        {
          if ( !o()->legendary.sephuzs_secret )
            return;

          // trigger by default on interrupts and on adds/lower level stuff
          if ( o()->allow_sephuz || mechanic == MECHANIC_INTERRUPT || state->target->is_add() ||
            ( state->target->level() < o()->sim->max_player_level + 3 ) )
          {
            o()->buffs.sephuzs_secret->trigger();
          }
        }

        struct travel_t : public action_t
        {
          travel_t( player_t* player ) : action_t( ACTION_OTHER, "travel", player )
          {
            trigger_gcd = timespan_t::zero();
          }
          void execute() override { player->current.distance = 1; }
          timespan_t execute_time() const override { return timespan_t::from_seconds( player->current.distance / 33.0 ); }
          bool ready() override { return ( player->current.distance > 1 ); }
          bool usable_moving() const override { return true; }
        };

        action_t* create_action( const std::string& name,
          const std::string& options_str ) override
        {
          if ( name == "travel" ) return new travel_t( this );

          return pet_t::create_action( name, options_str );
        }
      };

      // Template for common warlock pet action code. See priest_action_t.
      template <class ACTION_BASE>
      struct warlock_pet_action_t : public ACTION_BASE
      {
      public:
      private:
        typedef ACTION_BASE ab; // action base, eg. spell_t
      public:
        typedef warlock_pet_action_t base_t;

        warlock_pet_action_t( const std::string& n, warlock_pet_t* p,
          const spell_data_t* s = spell_data_t::nil() ) :
          ab( n, p, s )
        {
          ab::may_crit = true;

          // If pets are not reported separately, create single stats_t objects for the various pet
          // abilities.
          if ( !ab::sim->report_pets_separately )
          {
            auto first_pet = p->owner->find_pet( p->name_str );
            if ( first_pet && first_pet != p )
            {
              auto it = range::find( p->stats_list, ab::stats );
              if ( it != p->stats_list.end() )
              {
                p->stats_list.erase( it );
                delete ab::stats;
                ab::stats = first_pet->get_stats( ab::name_str, this );
              }
            }
          }
        }
        virtual ~warlock_pet_action_t() {}

        warlock_pet_t* p()
        {
          return static_cast<warlock_pet_t*>( ab::player );
        }
        const warlock_pet_t* p() const
        {
          return static_cast<warlock_pet_t*>( ab::player );
        }

        virtual void execute()
        {
          ab::execute();

          // Some aoe pet abilities can actually reduce to 0 targets, so bail out early if we hit that
          // situation
          if ( ab::n_targets() != 0 && ab::target_list().size() == 0 )
          {
            return;
          }
        }

        warlock_td_t* td( player_t* t )
        {
          return p()->o()->get_target_data( t );
        }

        const warlock_td_t* td( player_t* t ) const
        {
          return p()->o()->get_target_data( t );
        }

        void init() override
        {
          action_t::init();

          if (p()->o()->specialization() == WARLOCK_DESTRUCTION)
          {
            ab::base_multiplier *= 1.0 + p()->o()->spec.destruction->effectN(3).percent();
          }
        }
      };

      struct warlock_pet_melee_t : public warlock_pet_action_t<melee_attack_t>
      {
        struct off_hand_swing : public warlock_pet_action_t<melee_attack_t>
        {
          off_hand_swing( warlock_pet_t* p, double wm, const char* name = "melee_oh" ) :
            warlock_pet_action_t<melee_attack_t>( name, p, spell_data_t::nil() )
          {
            school = SCHOOL_PHYSICAL;
            weapon = &(p->off_hand_weapon);
            weapon_multiplier = wm;
            base_execute_time = weapon->swing_time;
            may_crit = background = true;
            base_multiplier = 0.5;
          }
        };

        off_hand_swing* oh;

        warlock_pet_melee_t(warlock_pet_t* p, double wm = 1.0, const char* name = "melee") :
          warlock_pet_action_t<melee_attack_t>(name, p, spell_data_t::nil()), oh(nullptr)
        {
          school = SCHOOL_PHYSICAL;
          weapon = &(p->main_hand_weapon);
          weapon_multiplier = wm;
          base_execute_time = weapon->swing_time;
          may_crit = background = repeating = true;

          if (p->dual_wield())
            oh = new off_hand_swing(p, weapon_multiplier);
        }

        double action_multiplier() const override {
          double m = warlock_pet_action_t::action_multiplier();

          return m;
        }

        virtual void execute() override
        {
          if ( !player->executing && !player->channeling )
          {
            melee_attack_t::execute();
            if ( oh )
            {
              oh->time_to_execute = time_to_execute;
              oh->execute();
            }
          }
          else
          {
            schedule_execute();
          }
        }
      };

      struct warlock_pet_melee_attack_t : public warlock_pet_action_t < melee_attack_t >
      {
      private:
        void _init_warlock_pet_melee_attack_t()
        {
          weapon = &( player->main_hand_weapon );
          special = true;
        }

      public:
        warlock_pet_melee_attack_t( warlock_pet_t* p, const std::string& n ) :
          base_t( n, p, p -> find_pet_spell( n ) )
        {
          _init_warlock_pet_melee_attack_t();
        }

        warlock_pet_melee_attack_t( const std::string& token, warlock_pet_t* p, const spell_data_t* s = spell_data_t::nil() ) :
          base_t( token, p, s )
        {
          _init_warlock_pet_melee_attack_t();
        }
      };

      struct warlock_pet_spell_t : public warlock_pet_action_t < spell_t >
      {
      private:
        void _init_warlock_pet_spell_t()
        {
          parse_spell_coefficient( *this );
        }

      public:
        warlock_pet_spell_t( warlock_pet_t* p, const std::string& n ) :
          base_t( n, p, p -> find_pet_spell( n ) )
        {
          _init_warlock_pet_spell_t();
        }

        warlock_pet_spell_t( const std::string& token, warlock_pet_t* p, const spell_data_t* s = spell_data_t::nil() ) :
          base_t( token, p, s )
        {
          _init_warlock_pet_spell_t();
        }

        double cost() const override
        {
          double c = spell_t::cost();
          return c;
        }
      };

      namespace felhunter
      {
        struct felhunter_pet_t : public warlock_pet_t
        {
          felhunter_pet_t( sim_t* sim, warlock_t* owner, const std::string& name = "felhunter" );

          virtual void init_base_stats() override;

          virtual action_t* create_action( const std::string& name, const std::string& options_str ) override;
        };
      }
      namespace imp
      {
        struct imp_pet_t : public warlock_pet_t
        {
          imp_pet_t( sim_t* sim, warlock_t* owner, const std::string& name = "imp" );

          virtual action_t* create_action( const std::string& name, const std::string& options_str ) override;
        };
      }
      namespace succubus
      {
        struct succubus_pet_t : public warlock_pet_t
        {
          succubus_pet_t( sim_t* sim, warlock_t* owner, const std::string& name = "succubus" );
          virtual void init_base_stats() override;
          virtual action_t* create_action( const std::string& name, const std::string& options_str ) override;
        };
      }
      namespace voidwalker
      {
        struct voidwalker_pet_t : public warlock_pet_t
        {
          voidwalker_pet_t( sim_t* sim, warlock_t* owner, const std::string& name = "voidwalker" );
          virtual void init_base_stats() override;
          virtual action_t* create_action( const std::string& name, const std::string& options_str ) override;
        };
      }
      namespace felguard
      {
        struct felguard_pet_t : public warlock_pet_t
        {
          felguard_pet_t( sim_t* sim, warlock_t* owner, const std::string& name = "felguard" );
          virtual void init_base_stats() override;
          virtual double composite_player_multiplier(school_e school) const override;
          virtual action_t* create_action( const std::string& name, const std::string& options_str ) override;
          bool create_actions() override;
        };
      }
      namespace dreadstalker
      {
        struct dreadstalker_t : public warlock_pet_t
        {
          dreadstalker_t(sim_t* sim, warlock_t* owner);
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual void demise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace wild_imp {
        struct wild_imp_pet_t : public warlock_pet_t
        {
          action_t* firebolt;
          bool isnotdoge;
          wild_imp_pet_t(sim_t* sim, warlock_t* owner);
          virtual void init_base_stats() override;
          virtual action_t* create_action(const std::string& name,const std::string& options_str) override;
          virtual void arise() override;
          virtual void demise() override;
          //void trigger(int timespan, bool isdoge = false) override;
        };
      }
      namespace vilefiend
      {
        struct vilefiend_t : public warlock_pet_t
        {
          vilefiend_t(sim_t* sim, warlock_t* owner);
          virtual void init_base_stats() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace demonic_tyrant {
        struct demonic_tyrant_t : public warlock_pet_t
        {
          demonic_tyrant_t(sim_t* sim, warlock_t* owner, const std::string& name = "demonic_tyrant");
          virtual void init_base_stats() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace infernal {
        struct infernal_t : public warlock_pet_t
        {
          infernal_t(sim_t* sim, warlock_t* owner, const std::string& name = "infernal");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual void demise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace shivarra {
        struct shivarra_t : public warlock_pet_t
        {
          action_t* multi_slash;
          shivarra_t(sim_t* sim, warlock_t* owner, const std::string& name = "shivarra");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace darkhound {
        struct darkhound_t : public warlock_pet_t
        {
          action_t* fel_bite;
          darkhound_t(sim_t* sim, warlock_t* owner, const std::string& name = "darkhound");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace bilescourge {
        struct bilescourge_t : public warlock_pet_t
        {
          bilescourge_t(sim_t* sim, warlock_t* owner, const std::string& name = "bilescourge");
          virtual void init_base_stats() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace urzul {
        struct urzul_t : public warlock_pet_t
        {
          action_t* many_faced_bite;
          urzul_t(sim_t* sim, warlock_t* owner, const std::string& name = "urzul");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace void_terror {
        struct void_terror_t : public warlock_pet_t
        {
          action_t* double_breath;
          void_terror_t(sim_t* sim, warlock_t* owner, const std::string& name = "void_terror");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace wrathguard {
        struct wrathguard_t : public warlock_pet_t
        {
          action_t* overhead_assault;
          wrathguard_t(sim_t* sim, warlock_t* owner, const std::string& name = "wrathguard");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace vicious_hellhound {
        struct vicious_hellhound_t : public warlock_pet_t
        {
          action_t* demon_fang;
          vicious_hellhound_t(sim_t* sim, warlock_t* owner, const std::string& name = "vicious_hellhound");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace illidari_satyr {
        struct illidari_satyr_t : public warlock_pet_t
        {
          action_t* shadow_slash;
          illidari_satyr_t(sim_t* sim, warlock_t* owner, const std::string& name = "illidari_satyr");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace eyes_of_guldan {
        struct eyes_of_guldan_t : public warlock_pet_t
        {
          eyes_of_guldan_t(sim_t* sim, warlock_t* owner, const std::string& name = "eyes_of_guldan");
          virtual void init_base_stats() override;
          virtual void arise() override;
          virtual void demise() override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
      namespace prince_malchezaar {
        struct prince_malchezaar_t : public warlock_pet_t
        {
          prince_malchezaar_t(sim_t* sim, warlock_t* owner, const std::string& name = "prince_malchezaar");
          virtual void arise() override;
          virtual void demise() override;
          virtual void init_base_stats() override;
        };
      }

      namespace darkglare
      {
        struct darkglare_t : public warlock_pet_t
        {
          darkglare_t(sim_t* sim, warlock_t* owner, const std::string& name = "darkglare");
          virtual double composite_player_multiplier(school_e school) const override;
          virtual action_t* create_action(const std::string& name, const std::string& options_str) override;
        };
      }
    }

    namespace actions
    {
      struct warlock_heal_t
        : public heal_t
      {
        warlock_heal_t( const std::string& n, warlock_t* p, const uint32_t id ) :
          heal_t( n, p, p -> find_spell( id ) )
        {
          target = p;
        }

        warlock_t* p()
        {
          return static_cast<warlock_t*>( player );
        }
        const warlock_t* p() const
        {
          return static_cast<warlock_t*>( player );
        }
      };

      struct warlock_spell_t : public spell_t
      {
      private:
        void _init_warlock_spell_t()
        {
          may_crit = true;
          tick_may_crit = true;
          weapon_multiplier = 0.0;
          gain = player->get_gain( name_str );

          can_havoc = false;
          affected_by_destruction_t20_4pc = false;
          affected_by_deaths_embrace = false;
          destro_mastery = true;
          can_feretory = true;

          parse_spell_coefficient( *this );
        }

      public:
        gain_t * gain;

        mutable std::vector<player_t*> havoc_targets;
        bool can_havoc;
        bool havocd;
        bool affected_by_destruction_t20_4pc;
        bool affected_by_flamelicked;
        bool affected_by_odr_shawl_of_the_ymirjar;
        bool affected_by_deaths_embrace;
        bool destro_mastery;
        bool can_feretory;

        warlock_spell_t( warlock_t* p, const std::string& n ) :
          spell_t( n, p, p -> find_class_spell( n ) )
        {
          _init_warlock_spell_t();
        }

        warlock_spell_t( warlock_t* p, const std::string& n, specialization_e s ) :
          spell_t( n, p, p -> find_class_spell( n, s ) )
        {
          _init_warlock_spell_t();
        }

        warlock_spell_t( const std::string& token, warlock_t* p, const spell_data_t* s = spell_data_t::nil() ) :
          spell_t( token, p, s )
        {
          _init_warlock_spell_t();
        }

        warlock_t* p()
        {
          return static_cast<warlock_t*>( player );
        }
        const warlock_t* p() const
        {
          return static_cast<warlock_t*>( player );
        }

        warlock_td_t* td( player_t* t )
        {
          return p()->get_target_data( t );
        }

        const warlock_td_t* td( player_t* t ) const
        {
          return p()->get_target_data( t );
        }

        bool use_havoc() const
        {
          if ( !p()->havoc_target || target == p()->havoc_target || !can_havoc )
            return false;

          return true;
        }

        void reset() override
        {
          spell_t::reset();
        }

        void init() override
        {
          action_t::init();

          affected_by_flamelicked = false;
          havocd = false;

          affected_by_odr_shawl_of_the_ymirjar = data().affected_by( p()->find_spell( 212173 )->effectN( 1 ) );

          if (p()->specialization() == WARLOCK_DESTRUCTION)
          {
            if (data().affected_by(p()->spec.destruction->effectN(1)))
              base_dd_multiplier *= 1.0 + p()->spec.destruction->effectN(1).percent();

            if (data().affected_by(p()->spec.destruction->effectN(2)))
              base_td_multiplier *= 1.0 + p()->spec.destruction->effectN(2).percent();
          }

          if (p()->specialization() == WARLOCK_AFFLICTION)
          {
            if (data().affected_by(p()->spec.affliction->effectN(1)))
              base_dd_multiplier *= 1.0 + p()->spec.affliction->effectN(1).percent();

            if (data().affected_by(p()->spec.affliction->effectN(2)))
              base_td_multiplier *= 1.0 + p()->spec.affliction->effectN(2).percent();
          }

          if ( p()->talents.creeping_death->ok() )
          {
            if ( data().affected_by( p()->talents.creeping_death->effectN( 1 ) ) )
              base_tick_time *= 1.0 + p()->talents.creeping_death->effectN( 1 ).percent();
            if ( data().affected_by( p()->talents.creeping_death->effectN( 2 ) ) )
              dot_duration *= 1.0 + p()->talents.creeping_death->effectN( 2 ).percent();
          }
        }

        double cost() const override
        {
          double c = spell_t::cost();
          if (havocd)
          {
            return 0.0;
          }
          return c;
        }

        void execute() override
        {
          spell_t::execute();
          if (use_havoc() && execute_state->target == this->target && !havocd)
          {
            this->set_target(p()->havoc_target);
            this->havocd = true;
            spell_t::execute();
            this->havocd = false;
          }

          if ( hit_any_target && result_is_hit( execute_state->result ) && p()->talents.grimoire_of_sacrifice->ok() && p()->buffs.grimoire_of_sacrifice->up() )
          {
            bool procced = p()->grimoire_of_sacrifice_rppm->trigger();
            if ( procced )
            {
              p()->active.grimoire_of_sacrifice_proc->target = execute_state->target;
              p()->active.grimoire_of_sacrifice_proc->execute();
            }
          }

          if ( can_feretory && p()->legendary.feretory_of_souls && rng().roll( p()->find_spell( 205702 )->proc_chance() ) && dbc::is_school( school, SCHOOL_FIRE ) )
            p()->resource_gain( RESOURCE_SOUL_SHARD, 1.0, p()->gains.feretory_of_souls );
        }

        void consume_resource() override;

        void tick( dot_t* d ) override
        {
          spell_t::tick( d );

          if ( d->state->result > 0 && result_is_hit( d->state->result ) && td( d->target )->dots_seed_of_corruption->is_ticking() && id != p()->spells.seed_of_corruption_aoe->id )
            accumulate_seed_of_corruption( td( d->target ), d->state->result_amount );
        }

        void impact( action_state_t* s ) override
        {
          spell_t::impact( s );

          if ( s->result_amount > 0 && result_is_hit( s->result ) && td( s->target )->dots_seed_of_corruption->is_ticking()
            && id != p()->spells.seed_of_corruption_aoe->id )
          {
            accumulate_seed_of_corruption( td( s->target ), s->result_amount );
          }

          if (p()->talents.reverse_entropy->ok())
          {
            auto success = p()->buffs.reverse_entropy->trigger();
            if (success)
            {
              p()->procs.reverse_entropy->occur();
            }
          }
        }

        double composite_target_multiplier( player_t* t ) const override
        {
          double m = spell_t::composite_target_multiplier(t);

          auto td = this->td( t );

          if ( td->debuffs_eradication->check() )
            m *= 1.0 + td->debuffs_eradication->data().effectN( 1 ).percent();

          if ( p()->legendary.odr_shawl_of_the_ymirjar && target == p()->havoc_target && affected_by_odr_shawl_of_the_ymirjar  )
            m *= 1.0 + p()->legendary.odr_shawl_of_the_ymirjar->effectN( 1 ).percent();

          return m;
        }

        double action_multiplier() const override
        {
          double pm = spell_t::action_multiplier();

          if ( p()->mastery_spells.chaotic_energies->ok() && destro_mastery )
          {
            double destro_mastery_value = p()->cache.mastery_value() / 2.0;
            double chaotic_energies_rng;

            if ( p()->sets->has_set_bonus( WARLOCK_DESTRUCTION, T20, B4 ) && affected_by_destruction_t20_4pc )
              chaotic_energies_rng = destro_mastery_value;
            else
              chaotic_energies_rng = rng().range( 0, destro_mastery_value );

            pm *= 1.0 + chaotic_energies_rng + ( destro_mastery_value );
          }

          if (p()->specialization() == WARLOCK_DEMONOLOGY)
          {
            if (this->data().affected_by(p()->mastery_spells.master_demonologist->effectN(2)))
              pm *= 1.0 + p()->cache.mastery_value();
          }

          return pm;
        }

        resource_e current_resource() const override
        {
          return spell_t::current_resource();
        }

        double composite_target_crit_chance( player_t* target ) const override
        {
          double c = spell_t::composite_target_crit_chance( target );
          return c;
        }

        bool consume_cost_per_tick( const dot_t& dot ) override
        {
          bool consume = spell_t::consume_cost_per_tick( dot );
          return consume;
        }

        void extend_dot( dot_t* dot, timespan_t extend_duration )
        {
          if ( dot->is_ticking() )
          {
            dot->extend_duration( extend_duration, dot->current_action->dot_duration * 1.5 );
          }
        }

        static void accumulate_seed_of_corruption( warlock_td_t* td, double amount )
        {
          td->soc_threshold -= amount;

          if ( td->soc_threshold <= 0 )
            td->dots_seed_of_corruption->cancel();
        }
      };

      using residual_action_t = residual_action::residual_periodic_action_t<warlock_spell_t>;

      struct summon_pet_t : public warlock_spell_t
      {
        timespan_t summoning_duration;
        std::string pet_name;
        pets::warlock_pet_t* pet;

      private:
        void _init_summon_pet_t()
        {
          util::tokenize( pet_name );
          harmful = false;

          if ( data().ok() &&
            std::find( p()->pet_name_list.begin(), p()->pet_name_list.end(), pet_name ) ==
            p()->pet_name_list.end() )
          {
            p()->pet_name_list.push_back( pet_name );
          }
        }

      public:
        summon_pet_t( const std::string& n, warlock_t* p, const std::string& sname = "" ) :
          warlock_spell_t( p, sname.empty() ? "Summon " + n : sname ),
          summoning_duration( timespan_t::zero() ),
          pet_name( sname.empty() ? n : sname ), pet( nullptr )
        {
          _init_summon_pet_t();
        }

        summon_pet_t( const std::string& n, warlock_t* p, int id ) :
          warlock_spell_t( n, p, p -> find_spell( id ) ),
          summoning_duration( timespan_t::zero() ),
          pet_name( n ), pet( nullptr )
        {
          _init_summon_pet_t();
        }

        summon_pet_t( const std::string& n, warlock_t* p, const spell_data_t* sd ) :
          warlock_spell_t( n, p, sd ),
          summoning_duration( timespan_t::zero() ),
          pet_name( n ), pet( nullptr )
        {
          _init_summon_pet_t();
        }

        bool init_finished() override
        {
          pet = debug_cast< pets::warlock_pet_t* >( player->find_pet( pet_name ) );

          return warlock_spell_t::init_finished();
        }

        virtual void execute() override
        {
          pet->summon( summoning_duration );

          warlock_spell_t::execute();
        }

        bool ready() override
        {
          if ( !pet )
          {
            return false;
          }
          return warlock_spell_t::ready();
        }
      };

      struct summon_main_pet_t : public summon_pet_t
      {
        cooldown_t* instant_cooldown;

        summon_main_pet_t( const std::string& n, warlock_t* p ) :
          summon_pet_t( n, p ), instant_cooldown( p -> get_cooldown( "instant_summon_pet" ) )
        {
          instant_cooldown->duration = timespan_t::from_seconds( 60 );
          ignore_false_positive = true;
        }

        virtual void schedule_execute( action_state_t* state = nullptr ) override
        {
          warlock_spell_t::schedule_execute( state );

          if ( p()->warlock_pet_list.active )
          {
            p()->warlock_pet_list.active->dismiss();
            p()->warlock_pet_list.active = nullptr;
          }
        }

        virtual bool ready() override {
          if ( p()->warlock_pet_list.active == pet )
            return false;

          if ( p()->talents.grimoire_of_supremacy->ok() ) //if we have the uberpets, we can't summon our standard pets
            return false;

          return summon_pet_t::ready();
        }

        virtual void execute() override
        {
          summon_pet_t::execute();

          p()->warlock_pet_list.active = p()->warlock_pet_list.last = pet;

          if ( p()->buffs.grimoire_of_sacrifice->check() )
            p()->buffs.grimoire_of_sacrifice->expire();
        }
      };
    }

    namespace buffs
    {
      template <typename Base>
      struct warlock_buff_t : public Base
      {
      public:
        typedef warlock_buff_t base_t;
        warlock_buff_t( warlock_td_t& p, const std::string& name, const spell_data_t* s = spell_data_t::nil(), const item_t* item = nullptr ) :
          Base( p, name, s, item ) { }

        warlock_buff_t( warlock_t& p, const std::string& name, const spell_data_t* s = spell_data_t::nil(), const item_t* item = nullptr ) :
          Base( &p, name, s, item ) { }

      protected:
        warlock_t* p()
        {
          return static_cast<warlock_t*>( Base::source );
        }
        const warlock_t* p() const
        {
          return static_cast<warlock_t*>( Base::source );
        }
      };
    }
}
