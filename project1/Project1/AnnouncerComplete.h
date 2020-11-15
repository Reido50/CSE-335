/**
 * \file AnnouncerComplete.h
 *
 * \author Jonathan Lee
 *
 * Level complete message class displays upon level complete
 */

#pragma once
#include "Announcer.h"

 /** Class displays the Completed Levels */
class CAnnouncerComplete : public CAnnouncer
{
public:
    /// Default constructor
    CAnnouncerComplete() = delete;

    /// Copy Constructor
    CAnnouncerComplete(const CAnnouncerComplete&) = delete;

    /// Destructor
    ~CAnnouncerComplete();

    /// Constructor
    CAnnouncerComplete(CTowerGame* towerGame);

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitAnnouncer(this); }

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    virtual void Update(double elapsed) override;

private:
    /// Time left till deletion
    double mTimeTillDelete = 3;

    /// Ready to delete variable
    bool mDelete = false;
};

